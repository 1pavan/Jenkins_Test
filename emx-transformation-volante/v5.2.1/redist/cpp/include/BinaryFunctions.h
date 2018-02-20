#ifndef __BINARYFUNCTIONS_H__
#define __BINARYFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT BinaryFunctions {
public:
	static Binary toHexBinary(const vstring& val) {
		return Binary::fromHexString(val);
	}

	static vstring toHexString(const Binary& val) {
		return val.toHexString();
	}

	static vstring toASCIIString(const Binary& val) {
		return val.toString();
	}
	static Binary toASCIIBinary(const vstring& str) {
		return Binary(str);
	}
	static vstring toBase64String(const Binary& val)  {
		return val.toBase64String();
	}
	static Binary fromBase64String(const vstring& str) {
		return Binary::fromBase64String(str);
	}

	static vstring binaryToString(const Binary& val, const vstring&  encoding){
		return toASCIIString(val);
	}
	static Binary stringToBinary(const vstring& str, const vstring& encoding){
		return toASCIIBinary(str);
	}
  static bool byteEquals(const Binary& v1, const Binary& v2);

	static Binary plus(const Binary& v1, const Binary& v2) {
		return v1 + v2;
	}

	static Binary left(const Binary& str, int num_chars) {
		return mid(str, 0, num_chars);
	}

	static Binary right(const Binary& str, int num_chars) {
		return mid(str, (int)str.length() - num_chars, num_chars);
	}
	static Binary mid(const Binary& v1, int start_index, int num_chars);
	static Binary sub(const Binary& v1, int offset, int size) {
		return mid(v1, offset, size);
	}
	static int length(const Binary& v1) {
		return (int)v1.length();
	}
	static int byteAt(const Binary& v1, int index) {
		if(index < 0 || index >= (int)v1.length()) { 			
			THROW_EXCEPTION(TransformRuntimeException("Index out of range of binary."));
		}
		return v1.at(index);
	}

	static int getBinaryInt(const Binary& binary, bool signedValue, bool bigEndian)  {
		return getBinaryInt(binary, 0, (int)binary.length(), signedValue, bigEndian);
	}

	static int getBinaryInt(const Binary& binary, int offset, int length, bool signedValue, bool bigEndian);
	static dlong getBinaryLong(const Binary& binary, bool signedValue, bool bigEndian)  {
		return getBinaryLong(binary, 0, (int)binary.length(), signedValue, bigEndian);
	}
	static dlong getBinaryLong(const Binary& binary, int offset, int length, bool signedValue, bool bigEndian);


     static void setBinaryInt(Binary& bytes, int value, bool signedValue, bool bigEndian) {
        setBinaryInt(bytes, value, 0, bytes.length(), signedValue, bigEndian);
    }

     static void setBinaryInt(const Binary& bytes, int value, int offset, int length, bool signedValue, bool bigEndian);
     static void setBinaryLong(const Binary& bytes, dlong value, int offset, int length, bool signedValue, bool bigEndian);


private:
	static int getBinaryInt1(const Binary& binary, int offset, bool bigEndian, bool signedValue);
	static int getBinaryInt2(const Binary& binary, int offset, bool bigEndian, bool signedValue);
	static int getBinaryInt4(const Binary& binary, int offset, bool bigEndian);
	static dlong getBinaryInt4Unsigned(const Binary& binary, int offset, bool bigEndian);
	static int getBinaryInt4Private(const Binary& binary, int offset, bool bigEndian);
	static dlong getBinaryLong4Private(const Binary& binary, int offset, bool bigEndian);
	static dlong getBinaryInt8(const Binary& binary, int offset, bool bigEndian);

    static void setBinaryInt1(const Binary& bytes, int value, int offset, bool bigEndian, bool signedValue);

    static void setBinaryInt2(const Binary& bytes, int value, int offset, bool bigEndian, bool signedValue);

    static void setBinaryInt4(const Binary& bytes, int value, int offset, bool bigEndian);

    static void setBinaryInt4Unsigned(const Binary& bytes, dlong value, int offset, bool bigEndian);

    static void setBinaryInt4Private(const Binary& bytes, int value, int offset, bool bigEndian);

    static void setBinaryLong4Private(const Binary& bytes, dlong value, int offset, bool bigEndian);

    static void setBinaryInt8(const Binary& bytes, dlong value, int offset, bool bigEndian);

};

VOLANTE_NAMESPACE_END

#endif //__BINARYFUNCTIONS_H__
