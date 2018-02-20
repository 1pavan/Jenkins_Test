#ifndef __FCSFUNCTIONS_H__
#define __FCSFUNCTIONS_H__
#include "Object.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FCSFunctions {
public:    
	static Binary storePSSChecksum(const Binary& message);
	static Binary storePSSChecksum(const Binary& buf1, const Binary& buf2);
private:
	static void store_checksum(short *buf, short len);
};

VOLANTE_NAMESPACE_END

#endif //__FCSFUNCTIONS_H__
