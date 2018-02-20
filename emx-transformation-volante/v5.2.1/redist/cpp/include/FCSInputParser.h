#ifndef __FCSINPUTPARSER_H__
#define __FCSINPUTPARSER_H__


#include "LiteralList.h"
#include "InputParser.h"
#include "FCSLineTokenizer.h"

VOLANTE_NAMESPACE_BEGIN

class LineReader;

class VOLANTE_EXPORT FCSInputParser : public InputParser {
public:
protected:
	FCSInputParser() {
		reserveTrailerLine = true;
	}
	void parseInternal(ExternalObject*  obj, const char* bytes, int length, TransformContext& cxt);
	void parseInternal(ExternalObject*obj, LineReader& reader, TransformContext& cxt);
	void parseInternal(ExternalObject* externalObject, const Binary& input, TransformContext& cxt);
	virtual void parseHeader(DataObject* obj, LineReader& reader, TransformContext& cxt) = 0;
	virtual void parseData(DataObject* obj, LineReader& reader, TransformContext& cxt) = 0;
	virtual void parseTrailer(DataObject* obj, LineReader& reader, TransformContext& cxt);
	static void verifyISN(const CharSequence& isn, FCSLineTokenizer& tokenizer, int tokenMarker);
	void parseFirmToCMSTrailer(DataObject* trailerObject, LineReader& reader, TransformContext& cxt) ;

	void additionalLinesAtEndError();

protected:
    bool reserveTrailerLine;
    bool isReserveTrailerLine() {
        return reserveTrailerLine;
    }

    void setReserveTrailerLine(bool reserveTrailerLine) {
        this->reserveTrailerLine = reserveTrailerLine;
    }

};


VOLANTE_NAMESPACE_END

#endif //__FCSINPUTPARSER_H__
