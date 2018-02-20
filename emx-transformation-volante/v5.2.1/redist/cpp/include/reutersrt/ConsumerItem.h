#ifndef _RFA_ConsumerItem_h_
#define _RFA_ConsumerItem_h_

/**
	\class ConsumerItem ConsumerItem.h
	\brief
	Base class for basic item managament. It is a storage class used to 
	hold persistant information (item name, handle , etc) for an individual 
    message stream.

*/

#include "Common/RespStatus.h"
#include "Common/Handle.h"
#include <vector>

using namespace rfa::common;


class ReutersMessageHandler;
class ConsumerItem
{
public:
	typedef std::pair<ReutersMessageHandler*, void*> HandlerPair;
	typedef std::vector<HandlerPair> Handlers;

	///@name Constructors
	//@{	
	/// Constructor, takes access to application configuration
	ConsumerItem(const std::string & name);
	ConsumerItem();
	virtual ~ConsumerItem();
	//@}

	const std::string & getName() const;

	void setHandle(Handle &);
	Handle * handle();

	virtual void clear();

	int clientCount();

	void addClient();
	void removeClient();
	void addClient(ReutersMessageHandler* reutersMessageHandler, void* handler) {
		handlers.push_back(HandlerPair(reutersMessageHandler, handler));
		++_count;
	}
	void removeClient(ReutersMessageHandler* reutersMessageHandler, void* handler) {
			for(Handlers::iterator it = handlers.begin(); it != handlers.end(); ++it) {
				HandlerPair handlerPair = *it;
				if(reutersMessageHandler == handlerPair.first && 	handler == handlerPair.second) {
					it =  handlers.erase(it);
					--_count;
				}
			}
	}
	Handlers& getHandlers() {
		return handlers;
	}

	const static int Pending = 0;
	const static int CompletePending = 1;
	const static int Complete = 2;

protected:
	std::string _name;
	Handle * _handle;
	RespStatus _status;
	int _requestState;
	int _count;
	Handlers handlers;
};

inline ConsumerItem::ConsumerItem() : _requestState(Pending), _handle(0), 
 _count(0)
{

}


inline ConsumerItem::ConsumerItem(const std::string & name) : _requestState(Pending), _handle(0), 
 _count(0), _name(name)
{
}

inline ConsumerItem::~ConsumerItem()
{}

inline void ConsumerItem::clear()
{
	_name.clear();
	_handle = 0;  // TODO - check on mem managment, Handle's destructor is private
	RespStatus emptyStatus; 
	_status = emptyStatus;
	_requestState = Pending;
	_count = 0;

}

inline const std::string & ConsumerItem::getName() const 
{
	return _name; 
}

inline void ConsumerItem::addClient()
{
	_count++;
}

inline void ConsumerItem::removeClient()
{
	_count--;
}

/*
inline void ConsumerItem::setRespStatus(const RespStatus & status)
{
	_status = status;
}
*/
inline void ConsumerItem::setHandle(Handle & handle)
{
	_handle = &handle;
}
/*

inline const RespStatus & ConsumerItem::getRespStatus()
{
	return _status;
}*/

/*
inline int ConsumerItem::requestState()
{
	return _requestState;
}*/

inline Handle * ConsumerItem::handle()
{
	return _handle;
}

inline int ConsumerItem::clientCount()
{
	return _count;
}

#endif
