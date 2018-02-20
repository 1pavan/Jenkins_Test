#ifndef __LITERALVALUE_H__
#define __LITERALVALUE_H__
#include "Object.h"
#include "CharSequence.h"
VOLANTE_NAMESPACE_BEGIN
#define MAX_TOKENS_PER_LITERAL 10
template <class T>
class LiteralValue  {
public:
	LiteralValue(const vstring& literal, const T& mappedValue, int literalIndex) {
		this->literal = literal;
		this->mappedValue = mappedValue;
		this->literalIndex = literalIndex;
		/*
		tokenCount = 1;
		size_t spaceIndex = literal.find(' ');
		while(spaceIndex != vstring::npos) {
			++tokenCount;
			spaceIndex = literal.find(' ', spaceIndex +1);
		}*/
		tokenCount = tokenize(literal);
	}

	int tokenize(const vstring& line) {
			int nTokens = 0;
			if(!line.empty()) {
				size_t length = line.length();
				size_t start = 0;
				for(size_t i = 0; i < length;++i) {
					if(line[i] == ' ') {
						if(i > start) {
							literalTokens[nTokens++] = line.substr(start, i - start);
							start = i + 1;
						}
						else {
							start = i + 1;
						}
					}
					if(nTokens > MAX_TOKENS_PER_LITERAL- 2) {
						THROW_EXCEPTION(TransformException("Too many tokens in literal"));
					}
				}
				if(start != length) {
					literalTokens[nTokens++] = line.substr(start, length - start);
				}
			}
			return nTokens;
		}


	// Sort in the reverse order
	bool operator < (const LiteralValue& that) {
		return (literal> that.literal);
	}
	bool less (const LiteralValue& that) {
		return (literal> that.literal);
	}

	bool match(const vstring& nextToken) {
		return  nextToken == literal;
	}

    bool matchValue(const T& value) {
		return  value == mappedValue;
    }


	/*
	inline bool match(const CharSequence& nextToken) {
	return nextToken == literal;
	}*/
	/*
	inline bool match(FCSLineTokenizer& tokenizer) {
		return tokenizer.matchTokens(literal);
	}*/

    bool match(FCSLineTokenizer& tokenizer) {
        for (int i = 0; i < tokenCount; ++i) {
            const vstring& literalToken = literalTokens[i];
            const CharSequence& token = tokenizer.peekToken(i+1);
            if(!(literalToken == token)) {
                return false;
            }
        }
        return true;
    }

	const vstring& getLiteral() {
		return literal;
	}

	const vstring& toString() {
		return literal;
	}
	inline const T& getMappedValue() {
		return mappedValue;
	}

	inline int getTokenCount() {
		return tokenCount;
	}
private:
	vstring literal;
	T mappedValue;
	int literalIndex;
	int tokenCount;
	vstring literalTokens[MAX_TOKENS_PER_LITERAL];
};

VOLANTE_NAMESPACE_END

#endif //__LITERALVALUE_H__
