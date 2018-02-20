#ifndef __FCSWRITER_H__
#define __FCSWRITER_H__


#include "LiteralList.h"
#include "InputParser.h"
#include "FCSLineTokenizer.h"

VOLANTE_NAMESPACE_BEGIN

class LineReader;

class VOLANTE_EXPORT FCSOutputWriter : public AbstractSimpleOutputWriter {
public:
protected:
	FCSOutputWriter() {
		useFractions = true;
	}

	virtual void writeHeader(DataObject* obj, TransformContext& cxt);
	virtual void writeData(DataObject* obj, TransformContext& cxt)=0;
	virtual void writeTrailer(DataObject* obj, TransformContext& cxt);

	void initMessage();
	vstring endMessage();


    bool useFractions;

    bool isUseFractions() {
        return useFractions;
    }

    void setUseFractions(bool useFractions) {
        this->useFractions = useFractions;
    }

public:

protected:
	void writeToken(const vstring& token);

    void writeToken(const vstring& token1, const vstring& token2);

    void writeToken(char token);
    void writeToken(int token);

    void writeNumberToken(int token);

    void writeToken(const DateTime& token);

    void writeToken(double token);

    void writeNumberToken(const vstring& token);

    void writePrice(double value);

    vstring previousToken(int count);

    void addToPreviousToken(const vstring& toAdd, int count);

    void setPreviousToken(const vstring& toSet, int count);


    vstring getOutput();


    void initToken();
    void emptyLine();

    void finishLine();

    void handleException(TransformException& e, DataObject* obj);

    vstring writeFirmToCMSTrailer(DataObject* trailerObject, TransformContext& cxt);

private:
	vstring getFraction(double decimal);
    vstringbuffer toRet;
    static vstring LINE_FEED;
    StringList tokens;
};


VOLANTE_NAMESPACE_END

#endif //__FCSWRITER_H__
