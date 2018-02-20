#ifndef __SECTIONFUNCTIONS_H__
#define __SECTIONFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT SectionFunctions {
public:
	static DataObject* addElement(DataObjectSection* sec) {
        DataObject* obj = sec->createElement();
        sec->addElement(obj);
        return obj;
    }
    static void addElement(DataObjectSection* sec, DataObject* obj) {
        obj->setParentSection(sec);
        sec->addElement(obj);
    }

    static void removeElement(DataObjectSection* sec, DataObject* obj) {
        int index = sec->getElementIndex(obj);
        sec->removeElement(index);
    }
    static DataObject* removeElement(DataObjectSection* sec, int index) {
        DataObject* obj = sec->getElement(index);
        sec->removeElement(index);
        return obj;
    }
    static void removeAllElements(DataObjectSection* sec)  {
        sec->clear();
    }
};


VOLANTE_NAMESPACE_END



#endif //__SECTIONFUNCTIONS_H__
