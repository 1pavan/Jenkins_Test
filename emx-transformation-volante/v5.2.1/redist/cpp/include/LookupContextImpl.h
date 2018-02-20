#ifndef __LOOKUPCONTEXTIMPL_H__
#define __LOOKUPCONTEXTIMPL_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT LookupContextImpl : public ILookupContext {
	virtual Object* clone() const;
	Object* lookupComponent(const vstring& name);

	template <class T>
		T* lookupClass(T*& t, const vstring& name) {
			Object* obj = lookup(name);
			if(ObjectFactory* factory = dynamic_cast<ObjectFactory*>(obj)) {
				Object* inst = factory->create();
				if(T* noobj = dynamic_cast<T*>(inst)) {
					return t = noobj;
				}
			}
			THROW_EXCEPTION(NamingException("Unable to lookup '" + name + "'"));
		}
		template <class T>
			StringList lookupFactories(T* /* dummy */) {
				StringList messages;
				for(typename LookupContextMap::iterator it = getLookupContextList().begin(); it != getLookupContextList().end(); ++it) {
					vstring lookupName = it->first;
					Object* obj = it->second;
					if(ObjectFactory* factory = dynamic_cast<ObjectFactory*>(obj)) {
						Object* obj = factory->create();
						if(dynamic_cast<T*>(obj) != NULL) {
							messages.add(lookupName);
						}
						LookupContextMap::addObject(obj);
						LookupContextMap::deleteObject(obj);
					}
				}
				return messages;
			}


			/**
			*  Look up a NormalizedObject Mapper ( maps one NO to another)
			*/
			NormalizedObjectMappingFormat lookupNormalizedObjectMappingFormat(const vstring& name);
			Message lookupMessage(const vstring& name);
			ExternalMessage lookupExternalMessage(const vstring& name);
			BusinessTransaction lookupBusinessTransaction(const vstring& name);
			InternalMessage lookupInternalMessage(const vstring& name);
			MessageMapping lookupMessageMapping(const vstring& name);
			MessageFlow lookupMessageFlow(const vstring& name);
			InputFormat lookupInputFormat(const vstring& name);
			OutputFormat lookupOutputFormat(const vstring& name);
			IOutputProtocol* lookupOutputProtocol(const vstring& name);
			//BatchContext createBatchContext() throws javax.naming.NamingException;
			//void destroyBatchContext(BatchContext bc) throws TransformException,java.rmi.RemoteException,javax.naming.NamingException;
			/**
			*  Look up a Output Protocol
			*/
			//PersistenceManager lookupPersistenceManager(const vstring& name) throws javax.naming.NamingException;
			//ConnectionPool lookupDataSource(const vstring& name) throws TransformException,java.rmi.RemoteException,javax.naming.NamingException;
			StringList getExternalMessages();
			StringList getMessageMappings();
			StringList getMessageFlows();
			StringList getMessages();
			StringList getInternalMessages();
			StringList getInputFormats();
			StringList getOutputFormats();
			StringList getNormalizedObjectMappings();
			void bind(const vstring& name, Object* obj);
			void rebind(const vstring& name, Object* obj);
			Object* lookup(const vstring& name);
			void unbind(const vstring& name);

			typedef ObjectPtrMap<Object> LookupContextMap;
			static LookupContextMap& getLookupContextList();
};
//static LookupContextMap lookupContextList;

VOLANTE_NAMESPACE_END

#endif //__LOOKUPCONTEXTIMPL_H__

