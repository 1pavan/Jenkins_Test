#ifndef __VALIDATIONFUNTIONS_H__
#define __VALIDATIONFUNTIONS_H__

VOLANTE_NAMESPACE_BEGIN

/*
*  ValidationFunctions.h
*
*  © Copyright 2001-2006 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/
class VOLANTE_EXPORT ValidationFunctions {

public:
	static void validate(bool condition, const vstring& errorCode, const vstring& errorMessage);

	static bool between(int value, int from, int to);
	static bool between(float value, float from, float to);

	static bool between(double value, double from, double to);
	static bool between(dlong value, dlong from, dlong to);
	static bool between(const DateTime& value, const DateTime& from, const DateTime& to);

	static bool valueIn(bool value, int count, ...);
	static bool valueIn(int value, int count, ...);
	static bool valueIn(dlong value, int count, ...);
	static bool valueIn(float value, int count, ...);
	static bool valueIn(double value, int count, ...);
	static bool valueIn(char value, int count, ...);
	static bool valueIn(const vstring& value, int count, ...);
	static bool valueIn(const char* value, int count, ...);
	static bool valueIn(const DateTime& value, int count, ...);
};
VOLANTE_NAMESPACE_END

#endif //__VALIDATIONFUNTIONS_H__

