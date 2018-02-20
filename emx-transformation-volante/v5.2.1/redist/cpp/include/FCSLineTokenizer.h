#ifndef __FCSLINETOKENIZER_H__
#define __FCSLINETOKENIZER_H__
#include "CharSequence.h"

VOLANTE_NAMESPACE_BEGIN

#define MAX_TOKENS_PER_LINE 50
class VOLANTE_EXPORT FCSLineTokenizer {
	FCSLineTokenizer(const FCSLineTokenizer&);
public:    
	FCSLineTokenizer();
	FCSLineTokenizer(const CharSequence& line);

	int getColumn();
	void setString(const CharSequence& line);

	CharSequence getLine();
	CharSequence peekLine();
	int getLineLength();

	bool isEmpty();

	const CharSequence& getNextToken();

	const CharSequence&  getNextToken(int count);
	CharSequence getTillToken(int count);

	void reset();

	int getTokenCount();

	const CharSequence&  peekNextToken();
	CharSequence peekTokenList(int index);

	const CharSequence&  peekToken(int index);
	const CharSequence&  previousToken(int index);
	int mark();
	void skip(int tokens);
	void skipToEnd();
	void reset(int newTokenIndex);
	void pushback(const CharSequence& token);

	CharSequence getRest();
	CharSequence peekRest();
	bool hasMoreTokens();
	bool matchTokens(const vstring& toMatch);
	void assertEmpty(const char* lineNumber);
	CharSequence getNumberType(int length, bool exact);

	CharSequence getCharType(int length, bool exact);
	bool isCharType(int length, bool exact);
	bool isAlphaNumericType(int length, bool exact);
	bool isTextType(int length, bool exact);

	static bool isNumberType(const CharSequence& str, size_t length);
	static bool isCharType(const CharSequence& str, size_t length);
	static bool isAlphaNumericType(const CharSequence& str, size_t length);
	static bool isTextType(const CharSequence& str, size_t length);

	static bool isCharType(char c) {
		return c >= 'A' && c <= 'Z';
	}
	static bool isNumberType(char c) {
		return c >= '0' && c <= '9';
	}
	static bool isAlphaNumericType(char c) {
		return (c >= 'A' && c <= 'Z') || (c >= '0' || c <= '9');
	}
	static bool isTextType(char c) {
		return c >= 0 && c <= 127;
	}

	bool isPrice();
	double parsePrice();
	bool isEmptyLine();
    bool hasFullLine() {
        return currentTokenIndex == 0;
    }

public:
	void lineLengthError(const char* lineNumber, int allowedLineLength);
	void missingFieldError(const char* lineNumber, const vstring& fieldName);
	void emptyLineError();
	void additionalLinesAtEndError();

private:
	void tokenize();
private:
	CharSequence line;
	CharSequence tokens[MAX_TOKENS_PER_LINE];
	int currentTokenIndex;
	int nTokens;

};

VOLANTE_NAMESPACE_END

#endif //__FCSLINETOKENIZER_H__
