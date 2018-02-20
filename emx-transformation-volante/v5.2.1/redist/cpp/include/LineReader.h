#ifndef __LINEREADER_H__
#define __LINEREADER_H__
#include "CharSequence.h"

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT LineReader {
	typedef ArrayList<CharSequence> CharSequenceList;
	CharSequenceList lines;
	int currentLine; 
	int lineCount;   
	bool reserveTrailerLine;

	CharSequence trailerLine;
private:
	LineReader(const LineReader&);
public:
	LineReader(InputSource& is, bool reserveTrailerLine) ;
	LineReader(const Binary& source, bool reserveTrailerLine);

	LineReader(const char* bytes, int length,  bool reserveTrailerLine) ;
	void reset();
	int getLastLineNumber();
	CharSequence getNextLine();
	bool hasMoreLines();
	CharSequence getTrailerLine() {
		return trailerLine;
	}
    void pushBackLine();
private:
	void readLines(const char* bytes, int length);
};

VOLANTE_NAMESPACE_END

#endif //__LINEREADER_H__
