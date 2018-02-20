#ifndef __DATAOBJECTIO_H__
#define __DATAOBJECTIO_H__
#include "Transform.h"
#include "ByteBuffer.h"
#include <sstream>
#define EIGHTH_BIT_SET (1 << 7)
#define EIGHTH_BIT_CLEARED (0xFF & (~EIGHTH_BIT_SET))
VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT DataObjectIO {
public:
	static Binary serialize(DataObject* obj);
	static void parse(DataObject* obj, const Binary& data);
	static void parse(DataObject* obj, const char* data, int count);
public:
	static void write(DataObject* obj, ByteBuffer& out);
	static void read(DataObject* obj, ByteBuffer& in);
	static void writeString(ByteBuffer& out, const vstring& str);
	static vstring readString(ByteBuffer& in);
	static void writeFastUnsignedInt(ByteBuffer& out, unsigned int value);
	static unsigned int readFastUnsignedInt(ByteBuffer& in);
	static void writeIntBigEndian(ByteBuffer& out, int value);
	static void writeLongBigEndian(ByteBuffer& out, dlong value);
	static void writeDoubleBigEndian(ByteBuffer& out, double value);
	static void writeFloatBigEndian(ByteBuffer& out, float value);

	static int readIntBigEndian(ByteBuffer& out);
	static dlong readLongBigEndian(ByteBuffer& buffer);
	static float readFloatBigEndian(ByteBuffer& buffer);
	static double readDoubleBigEndian(ByteBuffer& buffer);

	static unsigned int setHighBit(unsigned int value) {
		return (value & 0xFF) | EIGHTH_BIT_SET;
	}

	static int clearHighBit(unsigned int b1) {
		return (b1 & EIGHTH_BIT_CLEARED);
	}

	static unsigned int clearHighBitLS(unsigned int b1, int by) {
		return (b1 & EIGHTH_BIT_CLEARED) << by;
	}
	static void writeField(ByteBuffer& out, Object* fldVal, const vstring& type);
	static void readSetField(DataObject* obj, int index, ByteBuffer& in, const vstring& type);
	static void writeCompactDateTime(ByteBuffer& out, const DateTime& date, bool writeDate, bool writeTime);
	static DateTime readCompactDateTime(ByteBuffer& in, bool readDate, bool readTime);

};
VOLANTE_NAMESPACE_END

#endif //__DATAOBJECTIO_H__
