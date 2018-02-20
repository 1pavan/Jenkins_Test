#ifndef __LITERALLIST_H__
#define __LITERALLIST_H__
#include "Object.h"
#include <algorithm>
#include "FCSLineTokenizer.h"
#include "LiteralValue.h"

VOLANTE_NAMESPACE_BEGIN


template<class T, class ParamType>
class LiteralList {
	LiteralList(const LiteralList&);
public:
	typedef LiteralValue<T> Literal;
	typedef std::vector<Literal*> LiteralArray;     

	LiteralList(int count, const char* literalValues[], ParamType mappedValues[]) {
		for(int i =0; i< count;++i) {
			const char* literalValue = literalValues[i];
			ParamType mappedValue = mappedValues[i];
			literals.push_back(new Literal(literalValue, mappedValue, i));
		}
		init();
	}

	~LiteralList() {
		size_t length = literals.size();
		for(size_t i = 0;i < length;++i) {
			Literal* literal = literals[i];
			delete literal;
		}
	}
    vstring matchValue(const T& value) {
        size_t length = literals.size();
        for (size_t i = 0; i < length; ++i) {
            Literal* literal = literals[i];
            if (literal->matchValue(value)) {
				return literal->getLiteral();
            }
        }
		return vstring("");
    }
	class Comparator {
	public:
		bool operator() (Literal* l1, Literal* l2) {
			return l1->less(*l2);
		}

	};
	void init() {
		std::sort(literals.begin(), literals.end(), Comparator());
		checkMultiToken();
	}

	bool isMatch(FCSLineTokenizer& tokenizer) {
		return getMatch(tokenizer) != NULL;
	}

	Literal* match(FCSLineTokenizer&  tokenizer) {
		Literal* match = getMatch(tokenizer);
		if(match != NULL) {
			tokenizer.skip(match->getTokenCount());
		}
		return match;
	}

private:
	Literal* getMatch(FCSLineTokenizer& tokenizer) {
		if(tokenCount == 1) {
			return getMatchOptimized1(tokenizer);
		}
		else {
			size_t length = literals.size();
			for(size_t i = 0;i < length;++i) {
				Literal* literal = literals[i];
				if(literal->match(tokenizer)) {
					return literal;
				}
			}
		}
		return NULL;
	}

	Literal* getMatchOptimized1(FCSLineTokenizer& tokenizer) {
		CharSequence nextToken1 = tokenizer.peekNextToken();
		size_t length = literals.size();
		for(size_t i = 0;i < length;++i) {
			Literal* literal = literals[i];
			if(literal->match(nextToken1)) {
				return literal;
			}
		}
		return NULL;
	}
	/*
	Literal* getMatchOptimized2(FCSLineTokenizer& tokenizer) {
		CharSequence nextToken1 = tokenizer.peekNextToken();
		CharSequence nextToken2 = tokenizer.peekToken(2);
		CharSequence nextTwoTokens = (nextToken2.empty() ? nextToken1 : nextToken1.span(nextToken2));
		size_t length = literals.size();
		for(size_t i = 0;i < length;++i) {
			Literal* literal = literals[i];
			if(literal->match(literal->getTokenCount() == 1 ? nextToken1 : nextTwoTokens)) {
				return literal;
			}
		}
		return NULL;
	}
*/

	void checkMultiToken() {
        tokenCount = 1;
		size_t length = literals.size();
		for(size_t i = 0;i < length;++i) {
			Literal* literal = literals[i];
			int req = literal->getTokenCount();
			if(tokenCount < req) {
				tokenCount = req;
			}
        }
	}
private:
	LiteralArray literals;
    int tokenCount;
};

VOLANTE_NAMESPACE_END

#endif //__LITERALLIST_H__
