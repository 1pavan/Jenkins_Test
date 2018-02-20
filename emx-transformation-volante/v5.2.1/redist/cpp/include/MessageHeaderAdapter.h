#ifndef __MESSAGEHEADERADAPTER_H__
#define __MESSAGEHEADERADAPTER_H__

VOLANTE_NAMESPACE_BEGIN

class  VOLANTE_EXPORT MessageHeaderAdapter : public MessageHeader {
	DataObject* obj;
	bool own;
public:
	MessageHeaderAdapter(DataObject* obj, bool own =false) {
		this->obj = obj;
		this->own = own;

	}
	~MessageHeaderAdapter() {
		if(own) {
			delete obj;
		}
	}
	vstring getMessageFormat() const {
		return getHeaderField("MessageFormat");
	}
	vstring getMessageType() const {
		return getHeaderField("MessageType");
	}
	vstring getMessageVersion() const {
		return getHeaderField("MessageVersion");
	}
	vstring getHeaderField(const vstring& fieldName) const {
		ObjectVal toRet(obj->getField(fieldName));
		if(toRet.get() != NULL) {
			return toRet->toString();
		}
		return "";

	}
};

VOLANTE_NAMESPACE_END

#endif //__MESSAGEHEADERADAPTER_H__
