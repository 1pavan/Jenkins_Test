#ifndef __FIXHEADERPARSER_H__
#define __FIXHEADERPARSER_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT FIXHeaderParser {
public:
	void parseHeader(FIXHeader& header, const char* recordStr, int recordLength);
private:
	void parseHeader(FIXHeader* headerObj, FIXTokenizer& tokenizer);
};

VOLANTE_NAMESPACE_END

#endif //__FIXHEADERPARSER_H__
