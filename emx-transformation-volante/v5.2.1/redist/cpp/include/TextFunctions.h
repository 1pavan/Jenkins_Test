#ifndef __TEXTFUNCTIONS_H__
#define __TEXTFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

class VOLANTE_EXPORT ConcatFunctionsHelper {
public:
	static inline size_t lengthOf(const vstring& val) {
		return val.length();
	}
	static inline size_t lengthOf(char val) {
		return 1;
	}
	static inline size_t lengthOf(int val) {
		return 10;
	}
	static inline size_t lengthOf(double val) {
		return 15;
	}
	static inline size_t lengthOf(float val) {
		return 15;
	}
	static inline size_t lengthOf(dlong val) {
		return 15;
	}
	static inline size_t lengthOf(bool val) {
		return 4;
	}
	static inline size_t lengthOf(const Binary& val) {
		return val.length();
	}
	static inline size_t lengthOf(const char* val) {
		return strlen(val);
	}
	static inline size_t lengthOf(const DateTime& val) {
		return 20;
	}
	static inline size_t lengthOf(const BigInteger& val) {
		return 30;
	}
	static inline size_t lengthOf(const BigDecimal& val) {
		return 40;
	}
	static inline void appendToString(vstringbuffer& buffer, const vstring& val) {
		buffer.append(val);
	}
	static inline void appendToString(vstringbuffer& buffer, char val) {
		buffer += val;
	}
	static inline  void appendToString(vstringbuffer& buffer, int val) {
		char temp[35];
		intToString(val, temp);
		buffer.append(temp);
	}
	static inline  void appendToString(vstringbuffer& buffer, double val) {
		char temp[55];
		doubleToString(val, temp);
		buffer.append(temp);
	}
	static inline  void appendToString(vstringbuffer& buffer, float val) {
		char temp[55];
		floatToString(val, temp);
		buffer.append(temp);
	}
	static inline  void appendToString(vstringbuffer& buffer, dlong val) {
		char temp[55];
		dlongToString(val, temp);
		buffer.append(temp);
	}
	static inline  void appendToString(vstringbuffer& buffer, bool val) {
		buffer.append(boolToString(val));
	}
	static inline  void appendToString(vstringbuffer& buffer, const Binary& val) {
		buffer.append(val.toString());
	}
	static inline  void appendToString(vstringbuffer& buffer, const char* val) {
		buffer.append(val);
	}
	static inline  void appendToString(vstringbuffer& buffer, const DateTime& val) {
		buffer.append(val.toString(vstring("MMM dd, yyyy")));
	}
	static inline  void appendToString(vstringbuffer& buffer, const BigInteger& val) {
		buffer.append(Parsing::bigIntegerToString(val));
	}
	static inline  void appendToString(vstringbuffer& buffer, const BigDecimal& val) {
		buffer.append(Parsing::bigDecimalToString(val));
	}

};
template<class T>
class ConcatFunctions : public ConcatFunctionsHelper {
public:
	template <class T1, class T2>
	inline static vstring concat(const T1& t1, const T2&  t2) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		return toRet;
	}

	template <class T1, class T2, class T3>
	inline static vstring concat(const T1& t1, const T2&  t2, const T3& t3) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + + lengthOf(t3)  + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		appendToString(toRet, t3);
		return toRet;
	}
	template <class T1, class T2, class T3, class T4>
	inline static vstring concat(const T1& t1, const T2&  t2, const T3& t3, const T4& t4) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + + lengthOf(t3)+ lengthOf(t4)  + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		appendToString(toRet, t3);
		appendToString(toRet, t4);
		return toRet;
	}
	template <class T1, class T2, class T3, class T4, class T5>
	inline static vstring concat(const T1& t1, const T2&  t2, const T3& t3,  const T4& t4, const T5& t5) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + + lengthOf(t3)+ lengthOf(t4)+ lengthOf(t5)  + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		appendToString(toRet, t3);
		appendToString(toRet, t4);
		appendToString(toRet, t5);
		return toRet;
	}

	template <class T1, class T2, class T3, class T4, class T5, class T6>
	inline static vstring concat(const T1& t1, const T2&  t2, const T3& t3,  const T4& t4, const T5& t5, const T6& t6) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + + lengthOf(t3)+ lengthOf(t4)+ lengthOf(t5)+ lengthOf(t6)  + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		appendToString(toRet, t3);
		appendToString(toRet, t4);
		appendToString(toRet, t5);
		appendToString(toRet, t6);
		return toRet;
	}
	template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	inline static vstring concat(const T1& t1, const T2&  t2, const T3& t3,  const T4& t4, const T5& t5, const T6& t6, const T7& t7) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + + lengthOf(t3)+ lengthOf(t4)+ lengthOf(t5)+ lengthOf(t6)+ lengthOf(t7)  + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		appendToString(toRet, t3);
		appendToString(toRet, t4);
		appendToString(toRet, t5);
		appendToString(toRet, t6);
		appendToString(toRet, t7);
		return toRet;
	}
	template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	inline static vstring concat(const T1& t1, const T2&  t2, const T3& t3,  const T4& t4, const T5& t5, const T6& t6, const T7& t7, const T8& t8) 
	{
		vstringbuffer toRet;
		toRet.reserve(lengthOf(t1) + lengthOf(t2) + + lengthOf(t3)+ lengthOf(t4)+ lengthOf(t5)+ lengthOf(t6)+ lengthOf(t7) + lengthOf(t8) + 2);
		appendToString(toRet, t1);
		appendToString(toRet, t2);
		appendToString(toRet, t3);
		appendToString(toRet, t4);
		appendToString(toRet, t5);
		appendToString(toRet, t6);
		appendToString(toRet, t7);
		appendToString(toRet, t8);
		return toRet;
	}
};
#ifdef _MSC_VER
#pragma warning(disable: 4275)  // non-DLL interface used as base for DLL-interface");
#endif 

class VOLANTE_EXPORT TextFunctions : public ConcatFunctions<vstring> {

private:
	static vstring lowercase(const vstring& str);
	static vstring uppercase(const vstring& str);
public:


	/**
	* Returns the length of sequence of characters in <i>str</i>.
	* If <i>str</i> is empty returns 0.
	*
	* @param str	any string.
	*/
	static int length(const vstring& str) {
		return (int)str.length();
	}

	/**
	* Returns the leftmost <i>num_chars</i> no.of characters from the string <i>str</i>.      
	* If num_chars <= 0, returns empty string. 
	* If the num_chars is greater than the str's length, returns the entire string.
	* 
	* @param   str   any string.
	* @param   num_chars   number of characters to get from the string.	
	*/
	static vstring left(const vstring& str, int num_chars);

	/**
	* Returns the rightmost <i>num_chars</i> no.of characters from the string <i>str</i>.
	* If num_chars <= 0, returns empty string. 
	* If the length is greater than the string's length, returns the entire string.    
	* 
	* @param   str   any string.
	* @param   num_chars   number of characters to get from the string.	
	*/
	static vstring right(const vstring& str, int num_chars);

	/**
	* Returns <i>num_chars</i> no.of characters from the string <i>str</i> starting from the <i>start_index</i> specified.
	* If num_chars <= 0, returns empty string. 
	* If start_index < 0, takes it to be 0.
	* If start_index >= str's length, returns empty string.
	* If 'num_chars' no.of chars are not available starting from start_index specified, 
	* returns the available chars from start_index till str's length.     
	* 
	* @param   str   any string.
	* @param   start_index  start index to get chars.
	* @param   num_chars   number of characters to get from the string.	
	*/
	static vstring mid(const vstring& str, int start_index, int num_chars);

	/**
	*	Returns true if <i>str1</i> equals <i>str2</i>, returns false otherwise. The Comparison is case-sensitive.
	*	If both str1 & str2 are empty, returns true. If only one of them is empty, returns false.
	*
	*  @param   str1   any string.
	*  @param   str2   string to be compared with str2.
	*/
	static bool equal(const vstring& str1, const vstring& str2) {
		return str1 == str2;
	}

	static bool equal(const vstring& str1, const char* str2) {
		return str1 == str2;
	}


	/**
	*	Returns true if <i>str1</i> notEquals <i>str2</i>, returns false otherwise. The Comparison is case-sensitive.
	*	If both str1 & str2 are empty, returns false. If only one of them is empty, returns true.
	*
	*  @param   str1   any string.
	*  @param   str2   string to be compared with str2.
	*/
	static bool notEqual(const vstring& str1, const vstring& str2) {
		return str1 != str2;
	}
	static bool notEqual(const vstring& str1, const char* str2) {
		return str1 != str2;
	}

	/**
	* Concatenates <i>str1</i> and <i>str2</i> and returns the result String. 
	*
	* @param   str1   any string.
	* @param   str2   string to concatenate with str1.	 
	*/
	/*
	static vstring concat(const vstring& str1, const vstring& str2);
	static vstring concat(const vstring& str1, const char* str2);
	static vstring concat(const char* str1, const vstring& str2);
	static vstring concat(const char* str1, const char* str2);
	static vstring concat(const vstring& str1, const vstring& str2, const vstring& str3);
	static vstring concat(const vstring& str1, const vstring& str2, const vstring& str3, const vstring& str4);
	static vstring concat(const vstring& str1, const vstring& str2, const vstring& str3, const vstring& str4, const vstring& str5);
	static vstring concat(const vstring& str1, const vstring& str2, const vstring& str3, const vstring& str4, const vstring& str5, const vstring& str6);
	*/
	/**
	* Concatenates <i>str</i> and <i>val</i> and returns the result String.     
	*
	* @param   str   any string.
	* @param   val   int value to concatenate with str.	 
	*/	
	//static vstring concat(const vstring& str, int val);

	/**
	* Concatenates <i>val</i> and <i>str</i> and returns the result String.     
	*
	* @param   val   any integer value.
	* @param   str   string to concatenate with val.	 
	*/
	//static vstring concat(int val, const vstring& str);

	/**
	* Concatenates <i>str</i> and <i>val</i> and returns the result String.     
	*
	* @param   str   any string.
	* @param   val   double value to concatenate with str.	 
	*/
	//static vstring concat(const vstring& str, double val);

	/**
	* Concatenates <i>val</i> and <i>str</i> and returns the result String.     
	*
	* @param   val   any double value.
	* @param   str   string to concatenate with val.	 
	*/
	//static vstring concat(double val, const vstring& str);

	/**
	* Concatenates <i>str</i> and <i>val</i> and returns the result String.     
	*
	* @param   str   any string.
	* @param   val   float value to concatenate with str.	 
	*/
	//static vstring concat(const vstring& str, float val);

	/**
	* Concatenates <i>val</i> and <i>str</i> and returns the result String.     
	*
	* @param   val   any float value.
	* @param   str   string to concatenate with val.	 
	*/
	//static vstring concat(float val, const vstring& str);
	/*
	static vstring concat(const vstring&  str, dlong val) 
	{
		return str + dlongToString(val);
	}
	static vstring concat(dlong val, const vstring&  str) 
	{
		return dlongToString(val) + str;
	}

	static vstring concat(const vstring&  str, const DateTime& val) 
	{
		return str + val.toString(vstring("MMM dd, yyyy"));
	}
	static vstring concat(const DateTime& val, const vstring&  str) 
	{
		return val.toString(vstring("MMM dd, yyyy")) + str;
	}
	static vstring concat(const vstring&  str, char c) 
	{
		return str + charToString(c);
	}
	static vstring concat(char c, const vstring&  str) 
	{
		return charToString(c) + str;
	}
	static vstring concat( bool b, const vstring& str) 
	{
		return boolToString(b) + str;
	}
	static vstring concat( const vstring& str, bool b) 
	{
		return str + boolToString(b);
	}*/


	/**
	*  Returns the character at the specified <i>index</i> in <i>str</i>. Range of index is 
	*  0 to string length -1. 
	*  @param	str  any string.
	*  @param	index	index to get the character.
	*  @exception	TransformRuntimeException	if index < 0 or index >= str's length.
	*/
	static char charAt(const vstring& str, int index);

	/**
	* Converts the characters in <i>str</i> to lowercase and returns the converted string. 
	* If str is empty, returns empty string. 
	*
	* @param	str string to convert to lower case.
	*/
	static vstring lower(const vstring& str);

	/**
	* Converts the characters in <i>str</i> to uppercase and returns the converted string. 
	* If str is empty, returns empty string. 
	*
	* @param	str string to convert to upper case.
	*/
	static vstring upper(const vstring& str);

	/**
	*  Returns true if <i>str</i> starts with the prefix <i>start_text</i>. Returns false otherwise. 
	*  The check is case-sensitive. 
	*  If both str & start_text are empty, returns true. If only str is empty, returns false. 
	*  If start_text is empty string or equal to str, returns true.
	*  
	*  @param	str	any string 
	*  @param	start_text	string to be tested for prefix of str. 
	*/
	static bool startsWith(const vstring& str, const vstring& start_text) {
		return startsWith(str, start_text, 0);
	}

	/**
	*  Returns true if <i>str</i> starts with the prefix <i>start_text</i>. Returns false otherwise. 
	*  The check is not case-sensitive. 
	*  If both str & start_text are empty, returns true. If only str is empty, returns false. 
	*  If start_text is empty string or equal to str, returns true.
	*  
	*  @param	str	any string 
	*  @param	start_text	string to be tested for prefix of str. 
	*/
	static bool startsWithIgnoreCase(const vstring& str, const vstring& start_text);

	/**
	*  Returns true if <i>str</i> starts with the prefix <i>start_text</i> at <i>start_index.</i> 
	*  Returns false otherwise. The check is case-sensitive. 
	*  If both str & start_text are empty, returns true. If str is empty, returns false. 
	*  If start_text is empty string, returns true. 
	*  If start_index < 0, it is taken to be 0. If start_index >= str's length, returns false. 
	*
	*  @param	str	any string 
	*  @param	start_text	string to be tested for prefix of str. 
	*  @param	start_index		index from which prefix start_text is to be checked in str.
	*/
	static bool startsWith(const vstring& str, const vstring& start_text, int start_index);

	/**
	*  Returns true if <i>str</i> starts with the prefix <i>start_text</i> at <i>start_index.</i> 
	*  Returns false otherwise. The check is not case-sensitive. 
	*  If both str & start_text are empty, returns true. If str is empty, returns false. 
	*  If start_text is empty string, returns true. 
	*  If start_index < 0, it is taken to be 0. If start_index >= str's length, returns false. 
	*
	*  @param	str		any string 
	*  @param	start_text		string to be tested for prefix of str. 
	*  @param	start_index		index from which prefix start_text is to be checked in str.
	*/
	static bool startsWithIgnoreCase(const vstring& str, const vstring& start_text, int start_index);

	/**
	*  Returns true if <i>str</i> ends with the suffix <i>end_text</i>. Returns false otherwise. 
	*  The check is case-sensitive.
	*  If both str & end_text are empty, returns true. If str is empty, returns false. 
	*  If end_text is empty string or equal to str, returns true.
	*  
	*  @param	str	any string 
	*  @param	end_text	string to be tested for suffix of str. 
	*/
	static bool endsWith(const vstring& str, const vstring& end_text) {
		return str.rfind(end_text) == str.length() - end_text.length(); 
	}

	/**
	*  Returns true if <i>str</i> ends with the suffix <i>end_text</i>. Returns false otherwise. 
	*  The check is not case-sensitive.
	*  If both str & end_text are empty, returns true. If str is empty, returns false. 
	*  If end_text is empty string or equal to str, returns true.
	*  
	*  @param	str	any string 
	*  @param	end_text	string to be tested for suffix of str. 
	*/
	static bool endsWithIgnoreCase(const vstring& str, const vstring& end_text);

	/**
	*  Replaces all occurrences of <i>oldchar</i> with <i>newchar</i> in <i>str</i> and
	*  returns the result string. If oldchar does not occur in str, returns str. 
	*  If str is empty, returns empty string. 
	*
	*  @param	str	 string to replace a character with another character.
	*  @param	oldchar	 character to be replaced with new character.
	*  @param	newchar	 character to replace the old character.	
	*/
	static vstring replace(const vstring& str, char oldchar, char newchar);

	/**
	*  Replaces <i>num_chars</i> no.of characters starting from <i>start_index</i> in <i>str</i> with <i>newstr</i>. 
	*  If str is empty, returns empty string. 
	*  If start_index >= str's length or less than 0, or if num_chars < 0,
	*  returns the original string without any replacement. 
	*  If num_chars no.of chars are not available starting from start_index specified, 
	*  replaces the available chars from start_index till str's length. 
	*  If num_chars = 0, inserts newstr at start_index specified, not replacing any characters 
	*  (moves the characters towards right after insertion).
	*
	*  @param	str	 any string.
	*  @param	start_index  start index in str from which replacement takes place.	 	
	*  @param	num_chars	 no.of characters to be replaced.
	*  @param	newstr	new string to replace the substring in str.
	*/
	static vstring replace(const vstring& str, int start_index, int num_chars, const vstring& newstr);

	/**
	*  Replaces all occurrences of <i>oldstr</i> with <i>newstr</i> in <i>str</i> and returns the result string. 
	*  If str is empty, returns empty string.
	*  If oldstr is an empty string, returns str. 
	*  If oldstr does not occur in str, returns str. 
	*
	*  @param	str	any string
	*  @param	oldstr	substring in str to be replaced by newstr. 
	*  @param	newstr	string to replace oldstr.
	*/
	static vstring replace(const vstring& str, const vstring& oldstr, const vstring& newstr);

	/**
	*  Replaces character at <i>index</i> with <i>newchar</i> in <i>str</i> and returns the result. 
	*  If str is empty, returns empty string. 
	*  If index >= str's length or less than 0, returns the original string without any replacement. 
	*  
	*  @param	str	 any string. 
	*  @param	index	index of character to be replaced. 
	*  @param	newchar	 character to replace the existing character at specified index.	
	*/
	static vstring replace(const vstring& str, int index, char newchar) {
		vstring newstr(1, newchar);
		return replace(str, index, 1, newstr);
	}

	/**
	*	Replaces all occurrences of <i>oldstr</i> with <i>newchar</i> in <i>str</i> and 
	*  returns the result string. If str is empty, returns empty string. 
	*  If oldstr is an empty string, returns str. 
	*	If oldstr does not occur in str, returns str. 
	*
	*  @param	str	any string
	*  @param	oldstr	substring in str to be replaced by newchar. 
	*  @param	newchar	character to replace oldstr.
	*/
	static vstring replace(const vstring& str, const vstring& oldstr, char newchar) {
		vstring newstr(1, newchar);
		return replace(str, oldstr, newstr);
	}

	/**
	*	Replaces all occurrences of <i>oldchar</i> with <i>newstr</i> in <i>str</i> and returns the result string. 
	*  If str is empty, returns empty string. 
	*  If newstr is empty string, replaces oldchar with empty string. 
	*	If oldchar does not occur in str, returns str. 
	*
	*  @param	str	any string
	*  @param	oldchar	character to be replaced by newstr. 
	*  @param	newstr	new string to replace oldchar.
	*/
	static vstring replace(const vstring& str, char oldchar, const vstring& newstr) {
		vstring oldstr(1, oldchar);
		return replace(str, oldstr, newstr);
	}

	/**
	*  Removes white space from the left end of <i>str</i> and returns the result string.
	*  If str is empty, returns empty string.
	*
	*	@param	str any string
	*/
	static vstring trimLeft(const vstring& str);

	/**
	*  Removes white space from the right end of <i>str</i> and returns the result string.
	*  If str is empty, returns empty string.
	*
	*	@param	str any string
	*/
	static vstring trimRight(const vstring& str);

	/**
	*  Removes white space from both ends of <i>str</i> and returns the trimmed string.
	*  If str is empty, returns empty string.
	*
	*	@param	str any string
	*/
	static vstring trim(const vstring& str);


	static bool less(const vstring& str1, const vstring& str2) {
		return compare(str1, str2) < 0;
	}	
	static bool greater(const vstring& str1, const vstring& str2) {
		return compare(str1, str2) > 0;
	}	
	static bool lessEqual(const vstring& str1, const vstring& str2) {
		return compare(str1, str2) <= 0;
	}	
	static bool greaterEqual(const vstring& str1, const vstring& str2) {
		return compare(str1, str2) >= 0;
	}	


	/**
	*	Compares <i>str1</i> with <i>str2</i> lexicographically. Returns 0 if both are equal. Returns a value 
	*	less than 0 if str1 lesser than str2. Returns a value greater than 0 if str1 greater than str2.
	*	If both are empty, returns 0. If only str1 is empty, returns -1. If only str2 is empty, returns 1. 
	*
	*	@param	str1	any string.
	*	@param	str2	string to be compared with str1.
	*/
	static int compare(const vstring& str1, const vstring& str2) {
		return str1.compare(str2);
	}

	/**
	*	Compares <i>str1</i> with <i>str2</i> lexicographically, ignoring case. Returns 0 
	*	if both are equal. Returns a value less than 0 if str1 lesser than str2. 
	*	Returns a value greater than 0 if str1 greater than str2. 
	*	If both are empty, returns 0. If only str1 is empty, returns -1. 
	*	If only str2 is empty, returns 1. 
	*
	*	@param	str1	any string.
	*	@param	str2	string to be compared with str1.
	*/
	static int compareIgnoreCase(const vstring& str1, const vstring& str2) {
		return lower(str1).compare(lower(str2));
	}

	/**
	*	Returns the reversed sequence of characters in <i>str</i>.
	*	If str is empty, returns empty string.
	*	
	*	@param	str	any string.
	*/
	static vstring reverse(const vstring& str);

	/**
	*	Returns true if <i>str1</i> equals <i>str2</i>, returns false otherwise. The Comparison is not case-sensitive. 
	*	If both str1 & str2 are empty, returns true. If only one of them is empty, returns false.
	*
	*  @param   str1   any string.
	*  @param   str2   string to be compared with str2.
	*/
	static bool equalIgnoreCase(const vstring& str1, const vstring& str2) {
		return compareIgnoreCase(str1, str2)==0;
	}

	/**
	*	Returns true if <i>str1</i> notEquals <i>str2</i>, returns false otherwise. The Comparison is not case-sensitive. 
	*	If both str1 & str2 are empty, returns false. If only one of them is empty, returns true.
	*
	*  @param   str1   any string.
	*  @param   str2   string to be compared with str2.
	*/
	static bool notEqualIgnoreCase(const vstring& str1, const vstring& str2) {
		return compareIgnoreCase(str1, str2)!=0;
	}

	/**
	*	Inserts <i>insert_text</i> in <i>str</i> at the specified <i>index</i> and returns the string.
	*	If index specified is less than 0, it is taken to be 0, so 
	*	insert_text is inserted at index 0.	If index specified is greater than str's length, 
	*	it is taken to be withinStr's length, so insert_text is appended to withinStr. 
	*
	*	@param	str	any string. 	
	*	@param	index	index at which to insert insert_text in str.
	*	@param	insert_text	string to insert in str.
	*/
	static vstring insert(const vstring& str, int index, const vstring& insert_text);

	/**
	*	Inserts <i>insert_val</i> in <i>str</i> at the specified <i>index</i> and returns the string.
	*	If index specified is less than 0, it is taken to be 0, so 
	*	insert_val is inserted at index 0. If index specified is greater than str's length, 
	*	it is taken to be str's length, so insert_val is appended to str. 
	*
	*	@param	str	any string. 	
	*	@param	index	index at which to insert insert_val in str.
	*	@param	insert_val	integer value to insert in str.
	*/
	static vstring insert(const vstring& str, int index, int insert_val);

	/**
	*	Inserts <i>insert_val</i> in <i>str</i> at the specified <i>index</i> and returns the string.
	*	If index specified is less than 0, it is taken to be 0, so 
	*	insert_val is inserted at index 0. If index specified is greater than str's length, 
	*	it is taken to be str's length, so insert_val is appended to str. 
	*
	*	@param	str	any string. 	
	*	@param	index	index at which to insert insert_val in str.
	*	@param	insert_val	float value to insert in str.
	*/
	static vstring insert(const vstring& str, int index, float insert_val);

	/**
	*	Inserts <i>insert_val</i> in <i>str</i> at the specified <i>index</i> and returns the string.
	*	If index specified is less than 0, it is taken to be 0, so 
	*	insert_val is inserted at index 0. If index specified is greater than str's length, 
	*	it is taken to be str's length, so insert_val is appended to str. 
	*
	*	@param	str	any string. 	
	*	@param	index	index at which to insert insert_val in str.
	*	@param	insert_val	double value to insert in str.
	*/
	static vstring insert(const vstring& str, int index, double insert_val);

	/**
	*	Inserts <i>insert_char</i> in <i>str</i> at the specified <i>index</i> and returns the string.
	*	If index specified is less than 0, it is taken to be 0, so 
	*	insert_char is inserted at index 0. If index specified is greater than str's length, 
	*	it is taken to be str's length, so insert_char is appended to str. 
	*
	*	@param	str	any string. 	
	*	@param	index	index at which to insert insert_val in str.
	*	@param	insert_val	character value to insert in str.
	*/
	static vstring insert(const vstring& str, int index, char insert_char);

	/**
	*  Removes the character at the specified <i>index</i> in <i>str</i> and returns the string. 
	*  If str is empty returns empty string. If index specified is either less than 0, equal to or 
	*  greater than str's length, returns str without any alteration.
	*
	*  @param	str  any string.
	*  @param	index	index to remove the character.    
	*/
	static vstring deleteCharAt(const vstring& str, int index);

	/**
	*  Deletes <i>num_chars</i> no.of characters starting from <i>start_index</i> in <i>str</i>. 
	*  If str is empty, returns empty string. 
	*  If start_index >= str's length or less than 0, or if num_chars < 0,
	*  returns the original string without any alteration. 
	*  If num_chars no.of chars are not available starting from start_index specified, 
	*  deletes the available chars from start_index till str's length. 
	*
	*  @param	str	 any string.
	*  @param	index  index in str starting from which characters are deleted.
	*  @param	num_chars	 no.of characters to be deleted.
	*/
	static vstring deleteStr(const vstring& str, int index, int num_chars);

	/**
	*	Returns the substring in <i>str</i> which is to the left of <i>delimiterStr</i>.
	*  If str or delimiterStr is empty string, returns empty string. If delimiterStr is not found in 
	*  str, returns the entire string str. 
	*
	*	@param	str				any string.
	*	@param	delimiterStr	string which acts as the delimiter to get a substring uptil it's index from str. 
	*/
	static vstring leftStr(const vstring& str, const vstring& delimiterStr);

	/**
	*	Returns the substring in <i>str</i> which is to the right of <i>delimiterStr</i>.
	*  If str is empty returns empty string. If delimiterStr is empty, returns the 
	*  entire string str. If delimiterStr is not found in str, returns the entire string str.
	*
	*	@param	str				any string.
	*	@param	delimiterStr	string which acts as the delimiter to get a substring from str starting from it's index . 
	*/
	static vstring rightStr(const vstring& str, const vstring& delimiterStr);

	/**
	* Returns the index of first occurrence of character <i>charToFind</i> in <i>str</i>, searching 
	* from the specified <i>start_index</i> . The search is case-sensitive. 
	* If str is empty or if character charToFind is not found in str during the search, returns -1. 
	* If start_index is negative, it has the same effect as if it were zero: the entire string 
	* may be searched. If it is greater than the length of the string, it has the same effect 
	* as if it were equal to the length of this string: -1 is returned. 
	*
	* @param   str   any string.
	* @param   charToFind   character to be searched in str1.
	* @param   start_index   index in str, to start searching the character charToFind.
	*/
	static int findFirst(const vstring& str, char charToFind, int start_index);

	/**
	* Returns the index of first occurrence of character <i>charToFind</i> in <i>str</i>.
	* The search is case-sensitive. 
	* If str is empty or if character charToFind is not found in str, returns -1. 
	*
	* @param   str   any string.
	* @param   charToFind   character to be searched in str.	 
	*/
	static int findFirst(const vstring& str, char charToFind);

	/**
	* Returns the index of first occurrence of <i>strToFind</i> in <i>str</i>, searching from the 
	* specified <i>start_index.</i> The search is case-sensitive. 
	* If str is empty, returns -1. 
	* If strToFind is not found in str during the search, returns -1. 
	* If start_index is negative, it has the same effect as if it were zero: the entire string 
	* may be searched. If it is greater than the length of the string, it has the same effect 
	* as if it were equal to the length of this string: -1 is returned. 
	*
	* @param   str   any string.
	* @param   strToFind   substring to be searched in withinStr.
	* @param   start_index   index in withinStr, to start searching strToFind.	
	*/
	static int findFirst(const vstring& str, const vstring& strToFind, int start_index);

	/**
	* Returns the index of first occurrence of <i>strToFind</i> in <i>str</i>.
	* The search is case-sensitive. If str is empty, returns -1.
	* If strToFind is not found in str, returns -1. If strToFind is empty string returns 0.
	*  
	* @param   str   any string.
	* @param   strToFind   substring to be searched in str.	 
	*
	*/
	static int findFirst(const vstring& str, const vstring& strToFind);

	/**
	* Returns the index of rightmost occurrence of character <i>charToFind</i> in <i>str</i>, 
	* searching right to left from the <i>start_index</i> specified. 
	* The search is case-sensitive. If str is empty, returns -1.
	* If character charToFind is not found in str, returns -1. 
	* If start_index is greater than or equal to the length of this string, it has the same 
	* effect as if it were equal to one less than the length of this string: this entire
	* string may be searched. If it is negative, it has the same effect as if it were zero:
	* -1 is returned. 
	*
	* @param   str   any string.
	* @param   charToFind   character to be searched in str1.
	* @param   start_index   index in str1, to start searching the character c.	
	*/
	static int findLast(const vstring& str, char charToFind, int start_index);

	/**
	* Returns the index of last occurrence of character <i>charToFind</i> in <i>str</i>. 
	* The search is case-sensitive and is from right to left. 
	* If str is empty, returns -1.
	* If character charToFind is not found in str, returns -1. 
	*
	* @param   str   any string.
	* @param   charToFind   character to be searched in str.	 
	*/
	static int findLast(const vstring& str, char charToFind);

	/**
	* Returns the index of rightmost occurrence of <i>strToFind</i> in <i>str</i>, 
	* searching right to left from the specified start_index. 
	* The search is case-sensitive. If str is empty, returns -1. 
	* If strToFind is not found in str during the search, returns -1. 
	* If start_index is greater than the length of this string, it has the same effect as if it were
	* equal to the length of this string: this entire string may be searched. If it is
	* negative, it has the same effect as if it were zero: -1 is returned. 
	*
	* @param   str   any string.
	* @param   strToFind   substring to be searched in str.
	* @param   start_index   index in str, to start searching strToFind.	
	*/
	static int findLast(const vstring& str, const vstring& strToFind, int start_index);

	/**
	* Returns the index of last occurrence of <i>strToFind</i> in <i>str</i> . 
	* The search is case-sensitive. If str is empty, returns -1. 
	* If strToFind is not found in str, returns -1.
	*
	* @param   str   any string.
	* @param   strToFind   substring to be searched in str.
	*/
	static int findLast(const vstring& str, const vstring& strToFind);


	/**
	*	Pads the string <i>str</i> on the left with <i>pad_char</i> making the total length of 
	*	the string equal to <i>max_chars</i> and returns it. If <i>max_chars</i> is negative or 
	*	zero, returns empty string. If <i>max_chars</i> &lt; the length of <i>str</i>, returns 
	*	the substring of <i>max_chars</i> from <i>str</i> without any padding.
	*
	*	@param	str			string to be padded.
	*	@param	pad_char	character to pad the string.
	*	@param	max_chars	length of the string after padding.
	*/
	static vstring lpad(const vstring& str, char pad_char ,int max_chars);

	/**
	*	Pads the string <i>str</i> on the right with <i>pad_char</i> making the total length of 
	*	the string equal to <i>max_chars</i> and returns it. If <i>max_chars</i> is negative or 
	*	zero, returns empty string. If <i>max_chars</i> &lt; the length of <i>str</i>, returns 
	*	the substring of <i>max_chars</i> from <i>str</i> without any padding.
	*
	*	@param	str			string to be padded.
	*	@param	pad_char	character to pad the string.
	*	@param	max_chars	length of the string after padding.
	*/
	static vstring rpad(const vstring& str, char pad_char ,int max_chars);

	/**
	*	Repeats the string <i>str</i> <i>count</i> number of times and returns the string. 
	*	If <i>count</i> is negative or zero, returns empty string.
	*
	*	@param	str		string to be repeat.
	*	@param	count	number of times to be repeated.
	*/
	static vstring repeat(const vstring& str,int count);


	static bool isAlphaUpper(char c) ;
	static bool isAlphaUpper(const vstring& str);

	static bool isAlpha(char c) ;

	static bool isAlpha(const vstring& str);
	static inline bool isNum(char c) {
		return (c >= '0' && c <= '9');
	}
	static bool isNum(const vstring& str);
	static bool isAlphaNum(char c);
	static bool isAlphaNum(const vstring& str);

	static bool isAlphaUpperNum(char c);
	static bool isAlphaUpperNum(const vstring& str);
	static StringList split(const vstring& delimiterStr, const vstring& str);
	static StringList split(const vstring& delimiterStr, const vstring& str, int count);



	public:
    static vstringbuffer& append(vstringbuffer& buffer, const vstring& val) {
        return buffer.append(val);
    }
    static vstringbuffer& append(vstringbuffer& buffer, int val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, dlong val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, double val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, float val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, char val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, bool val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, const DateTime& val) {
			appendToString(buffer, val);
			return buffer;
    }

    static vstringbuffer& append(vstringbuffer& buffer, const ISODateTime& val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, const Binary& val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, const BigDecimal& val) {
			appendToString(buffer, val);
			return buffer;
    }
    static vstringbuffer& append(vstringbuffer& buffer, const BigInteger& val) {
			appendToString(buffer, val);
			return buffer;
    }

    static vstringbuffer& append(vstringbuffer& buffer, vstringbuffer& val) {
        return buffer.append(val);
    }
    static vstringbuffer createStringBuffer(int capacity) {
        return vstringbuffer();
    }
    static vstringbuffer createStringBuffer() {
        return vstringbuffer();
    }
};

VOLANTE_NAMESPACE_END

#endif //__TEXTFUNCTIONS_H__
