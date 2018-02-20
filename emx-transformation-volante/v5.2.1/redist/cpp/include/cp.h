#ifndef __CP_H__
#define __CP_H__

#define VOLANTE_CP_EXPORT
#pragma warning(disable: 4251)  // using non-exported as public in exported
#undef VOLANTE_CP_EXPORT
#ifdef CP_PROJECT
#define VOLANTE_CP_EXPORT PLATFORM_EXPORT
#else
#define VOLANTE_CP_EXPORT PLATFORM_IMPORT
#endif

#include <vector>
#include <map>
#include <string>

#endif //__CP_H__
