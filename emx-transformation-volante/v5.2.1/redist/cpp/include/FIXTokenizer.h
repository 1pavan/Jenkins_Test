#ifndef __FIXTOKENIZER_H__
#define __FIXTOKENIZER_H__
#include "Object.h"
#include "Exceptions.h"
#include "TransformException.h"
#include "FIXException.h"
#include "CharSequence.h"

VOLANTE_NAMESPACE_BEGIN

/*
*  FIXTokenizer.h
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
const char  keyValueSeparator = '=';
class VOLANTE_EXPORT FIXTokenizer {
public:
    class VOLANTE_EXPORT TagValuePair {
	public:   
		TagValuePair() {
		}
        TagValuePair(int tag, const CharSequence& value) {
            this->tag = tag;
            this->value = value;
        }
        
        int getTag() {
            return tag;
        }
        
        const CharSequence& getValue() {
            return value;
        }
        int toInt() {
			return Parsing::parseInt(toString());
        }
#ifdef VOLANTE_USE_STD_STRING
        vstring toString() {
            return value.toString();
        }
#else 
        const vstring& toString() {
            return value;
        }
#endif
		
		int tag;
        CharSequence value;
    };

    
public:
	FIXTokenizer(const CharSequence& sequence, char fieldDelimiter);
    
private:
	void init(const CharSequence& sequence, char fieldDelimiter);

	bool hasMoreTokens() {
        return currentIndex < (int)sequence.length();
    }
    
    CharSequence nextToken();
	CharSequence nextToken(int length);
    
public:
	void pushBack(const TagValuePair& nextTagPair) {
        this->nextTagPair = nextTagPair;
		hasNextTagValue = true;
    }
    int getTokenIndex(TagValuePair& pair);
    bool next(TagValuePair& nextTagPair) ;
	bool nextDataTag(TagValuePair& toRet, int length);

    int getCurrentIndex() {
        return currentIndex;
    }
    int getNextTokenIndex();
	void assertEmpty();
private:
    int currentIndex;
    int previousIndex;
    int recordLength;
    CharSequence sequence;
    char fieldDelimiter;
    TagValuePair nextTagPair;
	bool hasNextTagValue;
};

VOLANTE_NAMESPACE_END

#endif //__FIXTOKENIZER_H__
