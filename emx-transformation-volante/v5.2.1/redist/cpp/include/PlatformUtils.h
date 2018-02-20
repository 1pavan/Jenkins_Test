#ifndef __PLATFORMUTILS_H__
#define __PLATFORMUTILS_H__
#include "cp.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_CP_EXPORT PlatformUtils {
public:
	static unsigned long getTimeMillis();
	static vstring getFileName(const vstring& fullfilename);
	static vstring getAbsolutePath(const vstring& fullfilename);
	static vstring makeFile(const vstring& dir, const vstring& fileName);
	static StringList listFiles(const vstring& dir);
	static bool isDirectory(const vstring& dir);
	static bool renameTo(const vstring& file, const vstring& to);
	static bool deleteFile(const vstring& file);
	static vstring getCurrentDirectory();
	static bool isAbsoluteFile(const vstring& file);
	static bool fileExists(const vstring& file);
	static vstring getCanonicalPath(const vstring& file);
};

VOLANTE_NAMESPACE_END

#endif //__PLATFORMUTILS_H__

