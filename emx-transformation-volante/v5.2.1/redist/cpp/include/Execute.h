#ifndef __EXECUTE_H__
#define __EXECUTE_H__
#include "cp.h"

VOLANTE_NAMESPACE_BEGIN

class Tester;
class VOLANTE_CP_EXPORT Execute {
private:
	static bool pref;
	static int _loopCount;
	static int nthread;
	static int action;
	static bool autoFindLookupName;
	static void showSyntax();
	static Tester* getEntityTester(vstring lookupName, const StringList& args);
	static StringList consumeOptions(const StringList& args);
	friend class Tester;
	friend class MessageTester;

public:
	static int run(const StringList& args);
	
};

VOLANTE_NAMESPACE_END

#endif //__EXECUTE_H__
