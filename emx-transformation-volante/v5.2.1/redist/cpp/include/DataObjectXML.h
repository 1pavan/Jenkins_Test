#ifndef __DATAOBJECTXML_H__
#define __DATAOBJECTXML_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT DataObjectXML {
public:
    static vstring fixXMLCharData(const vstring& str) {
        return replaceXMLEntities(str, false);
    }
    
private:
    static bool hasNonXMLCharacters(const vstring& toWrite);
    static vstring replaceXMLEntities(const vstring& toWrite, bool attribute);
};

VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTXML_H__
