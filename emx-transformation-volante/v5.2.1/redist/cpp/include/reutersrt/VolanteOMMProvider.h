#ifndef __OMMPROVIDER_H__
#define __OMMPROVIDER_H__

#include "ReutersDll.h"
#include "IncludeReuters.h"

class REUTERS_EXPORT MessageInfo {
	rfa::common::UInt8 msgModelType;
public:
	MessageInfo() {
		this->msgModelType = 0;
	}
	MessageInfo(rfa::common::UInt8 msgModelType) {
		this->msgModelType = msgModelType;
	}
	UInt8 getMsgModelType() const {
		return msgModelType;
	}
};


class MessageProvider;
class REUTERS_EXPORT MessageManager {
protected:
	MessageInfo messageInfo;
	OMMProvider* pOmmProvider;
	std::string serviceName;
	typedef std::map<std::string, MessageProvider*> MessageProviders;
	MessageProviders messageProviders;
public:
	MessageManager(OMMProvider* pOmmProvider, const MessageInfo& messageInfo, const std::string& serviceName): pOmmProvider(pOmmProvider), messageInfo(messageInfo),serviceName(serviceName) {
	}
	MessageManager(const MessageInfo& messageInfo): pOmmProvider(pOmmProvider){
	}
	void setOMMProvider(OMMProvider* pOmmProvider) {
		this->pOmmProvider = pOmmProvider;
	}
	void setServiceName(const std::string& serviceName) {
		this->serviceName = serviceName;
	}
	const MessageInfo& getMessageInfo() const {
		return messageInfo;
	}
	MessageProvider* getMessageProvider(const std::string& name) {
		return messageProviders[name];
	}
	MessageProvider* getOrCreateMessageProvider(const std::string& name) {
		MessageProvider* provider = messageProviders[name];
		if(provider == NULL) {
			provider = createMessageProvider(name);
			messageProviders[name] = provider;
		}
		return provider;
	}
	virtual MessageProvider* createMessageProvider(const std::string& name) = 0;
};

template <class T>
class GenericMessageManager : public MessageManager {
public:
	GenericMessageManager(OMMProvider* pOmmProvider, const MessageInfo& messageInfo, const std::string& serviceName): MessageManager(pOmmProvider, messageInfo, serviceName) {

	}
	GenericMessageManager(const MessageInfo& messageInfo): MessageManager(NULL, messageInfo, "") {

	}
	virtual MessageProvider* createMessageProvider(const std::string& name) {
		MessageProvider* provider = new T(pOmmProvider, getMessageInfo(), serviceName, name);
		return provider;
	}
};

class REUTERS_EXPORT MessageProvider {
protected:
	MessageInfo messageInfo;
	std::string name;
	std::string serviceName;
	OMMProvider* pOmmProvider;
	bool _serviceUp;
public:
	MessageProvider(OMMProvider* pOmmProvider, const MessageInfo& messageInfo, const std::string& serviceName, const std::string& name) : pOmmProvider(pOmmProvider), messageInfo(messageInfo), serviceName(serviceName), name(name) {
		_serviceUp = true;
	}
	const MessageInfo& getMessageInfo() const {
		return messageInfo;
	}
	const std::string& getName() const {
		return name;
	}
	const std::string& getServiceName() const {
		return serviceName;
	}

	virtual void sendImage(RequestToken& token) =0;

	// send updates to all clients that have requested this domain/ric
	//virtual void sendUpdatesToAllRequestors()=0;

	void sendCommandToAllRequestors(OMMSolicitedItemCmd& itemCmd) {
		for (TOKEN_SET::iterator i = _tokens.begin();i != _tokens.end(); i++) {
			itemCmd.setRequestToken(**i);
			pOmmProvider->submit(&itemCmd);
		}
	}
	void sendMessage(RespMsg& _msg, RequestToken& token) {
    OMMSolicitedItemCmd itemCmd;
    itemCmd.setMsg(_msg);
    itemCmd.setRequestToken(token);
    pOmmProvider->submit(&itemCmd);
	}
	void sendMessageToAllRequestors(RespMsg& _msg) {
    OMMSolicitedItemCmd itemCmd;
    itemCmd.setMsg(_msg);
		for (TOKEN_SET::iterator i = _tokens.begin();i != _tokens.end(); i++) {
			itemCmd.setRequestToken(**i);
			pOmmProvider->submit(&itemCmd);
		}
	}

	void addToken(RequestToken* token) {
		_tokens.insert(token);
	}

	// remove token to indicate a client has closed this domain/ric combination
	bool removeToken(const RequestToken* token) {
		for (TOKEN_SET::iterator i = _tokens.begin();i != _tokens.end(); i++) {
			if ((*i)==(token)) {
				_tokens.erase(i);
				return true;
			}
		}
		return false;
	}

	// how many clients have requested this domain/ric combination?
	virtual int numTokens() const {
		return _tokens.size();
	}
private:
	typedef set<rfa::sessionLayer::RequestToken*> TOKEN_SET;
	TOKEN_SET _tokens;
};

class REUTERS_EXPORT ServiceProvider {
public:
	typedef std::vector<MessageManager*> MessageManagerList;
	typedef std::vector<MessageInfo> MessageInfoList;
	MessageManagerList managers;
	MessageInfoList messageInfos;
	std::string serviceName;
	ServiceProvider(const std::string& serviceName) :serviceName(serviceName) {

	}
	const std::string& getServiceName() {
		return serviceName;
	}
	MessageManager* getMessageManager(UInt8 msgModelType) {
		for(MessageManagerList::iterator it = managers.begin(); it != managers.end(); ++it) {
			MessageManager* manager = *it;
			if(manager->getMessageInfo().getMsgModelType() == msgModelType) {
				return manager;
			}
		}
		return NULL;
	}

	void addMessageManager(MessageManager* manager)  {
		managers.push_back(manager);
		messageInfos.push_back(manager->getMessageInfo());
	}
	MessageProvider* getMessageProvider(UInt8 msgModelType, const std::string& name) {
		MessageManager* manager = getMessageManager(msgModelType);
		if(manager != NULL) {
			return manager->getOrCreateMessageProvider(name);
		}
		return NULL;
	}
};

class OMMClient {
public:
	typedef std::set<RequestToken*> TOKEN_SET; //set of tokens requested by a client
	OMMClient(const Handle* clientHandle) {
		this->clientHandle = clientHandle;
		loggedIn = false;
	}
	TOKEN_SET& getTokens() {
		return tokens;
	}
	void removeToken(RequestToken* token)  {
		tokens.erase(token);
	}
	void addLoginToken(RequestToken* token)  {
		tokens.insert(token);
		loggedIn = true;
	}
	void addToken(RequestToken* token)  {
		tokens.insert(token);
	}
	bool containsToken(RequestToken* token) const  {
      TOKEN_SET::const_iterator tokenIter = tokens.find(token);
      if (tokenIter != tokens.end()) { //we got this token before                     
          return true;
      }
			return false;
	}
	bool isLoggedIn() {
		return loggedIn;
	}
	void setUserName(const std::string& str) {
		this->userName = str;
	}
	void setApplicationId(const std::string& str) {
		this->applicationId = str;
	}
	const std::string& getApplicationId() {
		return  applicationId;
	}
	const Handle* clientHandle;
	TOKEN_SET tokens;
	bool loggedIn;
	std::string applicationId;
	std::string userName;

};


class REUTERS_EXPORT VolanteOMMProvider : public Client {
public:

	VolanteOMMProvider(EventQueue* eventQueue, Session* session, const RFA_String& serviceName);
	virtual ~VolanteOMMProvider();
	void cleanup();
	void addMessageManager(MessageManager* manager);
protected:
	void init();

	void processEvent(const Event &event);
	void processCompletionEvent(const Event& event);
	void processOMMActiveClientSessionEvent(const OMMActiveClientSessionEvent &);
	void processOMMCmdErrorEvent(const OMMCmdErrorEvent&);
	void processConnectionEvent(const ConnectionEvent & event);
	void processOMMInactiveClientSessionEvent( const OMMInactiveClientSessionEvent &event );
	void processOMMSolicitedItemEvent(const OMMSolicitedItemEvent& event);

	void processClose(const Handle* clientSessionHandle, RequestToken & token);
	void processLogout(const Handle* clientSessionHandle);
	void processRequest(const Handle* clientSessionHandle, RequestToken & token, const ReqMsg & reqMsg);
	void sendLoginMsg(RequestToken & token, const ReqMsg & reqMsg, OMMClient* client);
	MessageProvider* getMessageProvider(const UInt8 msgModel, AttribInfo& attrib);
	void  dumpLoginAttributes(const AttribInfo& rAttribInfo, OMMClient* client) ;

	OMMClient* getClient(const Handle* handle) {
		return clients[handle];
	}
	OMMClient* createClient(const Handle* handle) {
		OMMClient* client =new OMMClient(handle);
		clients[handle] = client;
		return client;
	}
	bool removeClient(const Handle* handle) {
		CLIENT_MAP::iterator it = clients.find(handle);
		if(it != clients.end()) {
			clients.erase(it);
			return true;
		}
		return false;
	}
	MessageProvider* getMessageProvider(RequestToken* token) {
		return _token2MsgProviderMap[token];
	}
	void addMessageProvider(RequestToken* token, MessageProvider* provider) {
		_token2MsgProviderMap[token] = provider;
		if(provider != NULL) {
			provider->addToken(token);
		}
	}
	void removeToken(RequestToken* token) {
    MessageProvider* msg = getMessageProvider(token);
	  if (msg) {
        msg->removeToken(token);
		}
		_token2MsgProviderMap.erase(token);
	}

private:
	typedef std::map<const Handle*, OMMClient*> CLIENT_MAP;
	CLIENT_MAP clients;

	typedef std::map<RequestToken*, MessageProvider*> TOKEN2MSG_MAP;
	TOKEN2MSG_MAP _token2MsgProviderMap;

	ServiceProvider* serviceProvider;
	OMMProvider* _pOmmProvider;
	EventQueue* _eventQueue;
	Session* _session;

	Handle * _errHandle;
	Handle * _listenConnectionHandle;
	Handle * _listenHandle;

	bool _connectionUp;

	const RFA_String& _serviceName; 	
};

#define MAX_CLIENTS 20
#include "Timer.h"


class REUTERS_EXPORT VolanteMessageProvider : public MessageProvider, CTimerClient {
public:
	VolanteMessageProvider(OMMProvider* pOmmProvider, const MessageInfo& messageInfo, const std::string& serviceName, const std::string& name) : MessageProvider(pOmmProvider, messageInfo, serviceName, name) {
		init();
	}
	void init();
	void encodeMarketPriceFieldList(FieldList* pFieldList,RespMsg::RespType respType);
	virtual void sendImage(RequestToken& token);
	void processTimer(void* pClosure);
	void sendUpdatesToAllRequestors();
private:
  RespMsg _msg;
    int _priceVal;
    int _acVolVal;

};

#endif //__OMMPROVIDER_H__
