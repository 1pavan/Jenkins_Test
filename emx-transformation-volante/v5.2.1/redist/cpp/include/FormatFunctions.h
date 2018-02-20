#ifndef __FORMATFUNCTIONS_H__
#define __FORMATFUNCTIONS_H__

VOLANTE_NAMESPACE_BEGIN

/*
*  FormatFunctions.h
*
*  © Copyright 2001-2006 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/

/**
* class FormatFunctions consists of utility methods to help in formatting the given argument into
* the required string or parsing the given string argument into the required data.
* 
*/
class VOLANTE_EXPORT FormatFunctions {
public:
	static vstring toText(char ch) {
		return charToString(ch);
	}
	/**
	*  Returns the vstring representation of the int argument. 
	*
	*  @param	val	integer to be converted to vstring.	
	*/
	static vstring toText(int val) {
		return intToString(val);
	}
	/**
	*  Returns the vstring representation of the float argument. 
	*
	*  @param	val	float to be converted to vstring.	
	*/
	static vstring toText(float val) {
		return floatToString(val);
	}

	static vstring toText(double val) {
		return doubleToString(val);
	}

	static vstring toText(dlong val) {
		return dlongToString(val);
	}
	static vstring toText(bool val) {
		return boolToString(val);
	}

	static vstring toText(const char* str) {
		return vstring(str);
	}

	static vstring toText(const Binary& val) {
		return val.toString();
	}

	static bool isInt(const vstring& str);
	static bool isLong(const vstring& str);

	static bool isFloat(const vstring& str);
	static bool isDouble(const vstring& str);
	static bool isDate(const vstring& arg, const vstring& pattern);

	/**
	*  Returns the int representation (in decimal) of the vstring argument. 	 	
	*  @param	str	vstring to be converted to int. 	
	*  @exception	TransformRuntimeException	if str is not parsable to int.
	*/
	static int toInt(const vstring& str);
  static int toInt(char c) {
      return (int) c;
  }

	static dlong toLong(const vstring& str);
	/**
	*  Returns the double representation of the vstring argument. If the string is null, returns 0.	 	
	*  @param	str	vstring to be converted to double. 	
	*  @exception	TransformRuntimeException	if str is not parsable to double.
	*/
	static double toDouble(const vstring& str);
	/**
	*  Returns the float representation of the vstring argument. If the string is null returns 0.	 	
	*  @param	str	vstring to be converted to float. 	
	*  @exception	TransformRuntimeException	if str is not parsable to float.
	*/
	static float toFloat(const vstring& str);
	/**
	*  Returns the char representation of the vstring argument. 	 
	*  If str is null or str is empty string, it is taken to be a single space character.		
	*  If str's length is greater than 1, returns the first character. 
	*
	*  @param	str	vstring to be converted to char. 
	*/
	static char toChar(const vstring& str);

	static vstring formatDate(const DateTime& date);
	static vstring formatDate(const DateTime& date, const vstring& pattern);



	static DateTime parseDate(const vstring& arg);
	/**
	* Returns the date according to the argument arg. 
	* The pattern should atleast contain the day,month and the year to get proper results
	* On the basis of the the pattern arguments the string arg is parsed to get the date. So it is 
	* that the pattern should match the string arg format exactly. Some of the guidelines for creating the pattern strings
	* are given below.
	* <p> <blockquote>
	* <table border=0 cellspacing=3 cellpadding=0>
	*     <tr bgcolor="#ccccff">
	*         <th align=left>Letter
	*         <th align=left>Date 
	*         <th align=left>Presentation
	*         <th align=left>Examples
	*     <tr bgcolor="#eeeeff">
	*         <td><code>y</code>
	*         <td>Year
	*         <td><a href="#year">Year</a>
	*         <td><code>1996</code>; <code>96</code>
	*     <tr>
	*         <td><code>M</code>
	*         <td>Month in year
	*         <td><a href="#month">Month</a>
	*         <td><code>July</code>; <code>Jul</code>; <code>07</code>
	*     <tr bgcolor="#eeeeff">
	*         <td><code>w</code>
	*         <td>Week in year
	*         <td><a href="#number">Number</a>
	*         <td><code>27</code>
	*     <tr>
	*         <td><code>W</code>
	*         <td>Week in month
	*         <td><a href="#number">Number</a>
	*         <td><code>2</code>
	*     <tr bgcolor="#eeeeff">
	*         <td><code>D</code>
	*         <td>Day in year
	*         <td><a href="#number">Number</a>
	*         <td><code>189</code>
	*     <tr>
	*         <td><code>d</code>
	*         <td>Day in month
	*         <td><a href="#number">Number</a>
	*         <td><code>10</code>
	*     <tr bgcolor="#eeeeff">
	*         <td><code>F</code>
	*         <td>Day of week in month
	*         <td><a href="#number">Number</a>
	*         <td><code>2</code>
	*     <tr>
	*         <td><code>E</code>
	*         <td>Day in week
	*         <td><a href="#text">Text</a>
	*         <td><code>Tuesday</code>; <code>Tue</code>
	* </table>
	* </blockquote>
	* Pattern letters are usually repeated, as their number determines the
	* exact presentation:
	* <ul>
	* <li><strong><a name="text">Text:</a></strong>
	*     For formatting, if the number of pattern letters is 4 or more,
	*     the full form is used; otherwise a short or abbreviated form
	*     is used if available.
	*     For parsing, both forms are accepted, independent of the number
	*     of pattern letters.
	* <li><strong><a name="number">Number:</a></strong>
	*     For formatting, the number of pattern letters is the minimum
	*     number of digits, and shorter numbers are zero-padded to this amount.
	*     For parsing, the number of pattern letters is ignored unless
	*     it's needed to separate two adjacent fields.
	* <li><strong><a name="year">Year:</a></strong>
	*     For formatting, if the number of pattern letters is 2, the year
	*     is truncated to 2 digits; otherwise it is interpreted as a
	*     <a href="#number">number</a>.
	*     <p>For parsing, if the number of pattern letters is more than 2,
	*     the year is interpreted literally, regardless of the number of
	*     digits. So using the pattern "MM/dd/yyyy", "01/11/12" parses to
	*     Jan 11, 12 A.D.
	*     <p>For parsing with the abbreviated year pattern ("y" or "yy"),
	*     <code>SimpleDateFormat</code> must interpret the abbreviated year
	*     relative to some century.  It does this by adjusting dates to be
	*     within 80 years before and 20 years after the time the <code>SimpleDateFormat</code>
	*     instance is created. For example, using a pattern of "MM/dd/yy" and a
	*     <code>SimpleDateFormat</code> instance created on Jan 1, 1997,  the string
	*     "01/11/12" would be interpreted as Jan 11, 2012 while the string "05/04/64"
	*     would be interpreted as May 4, 1964.
	*     During parsing, only strings consisting of exactly two digits, as defined by
	*     {@link Character#isDigit(char)}, will be parsed into the default century.
	*     Any other numeric string, such as a one digit string, a three or more digit
	*     string, or a two digit string that isn't all digits (for example, "-1"), is
	*     interpreted literally.  So "01/02/3" or "01/02/003" are parsed, using the
	*     same pattern, as Jan 2, 3 AD.  Likewise, "01/02/-3" is parsed as Jan 2, 4 BC.
	* <li><strong><a name="month">Month:</a></strong>
	*     If the number of pattern letters is 3 or more, the month is
	*     interpreted as <a href="#text">text</a>; otherwise,
	*     it is interpreted as a <a href="#number">number</a>.
	* </ul>
	* <p>The arg and pattern combination can be like
	*<ul><li> "2002/01/25" and "yyyy/MM/dd" 
	*<li>"25/01/2002" and "dd/MM/yyyy"
	*<li>"25.January.02" and "dd.MMMM.yy"
	*<li>"January 25 2002" and "MMMM dd yyyy"    		
	*<li>"Fri, Jan 25, '02" and "EEE, MMM d, ''yy" 
	* @param arg the String value of the date 
	* @param pattern the String specifying the user pattern which helps in parsing the arg
	* @return the date parsed from the given String arg.
	* @exception TransformRuntimeException if the string arg does not contain valid date data
	* @exception TransformRuntimeException if the string pattern contains invalid matching pattern
	* @exception TransformRuntimeException if the string pattern is null
	*/
	static DateTime parseDate(const vstring& arg, const vstring& pattern);



	static int toInt(const BigInteger& val) {
		return val.toInt();
	}
	static dlong toLong(const BigInteger& val) {
		return val.toLong();
	}
	static float toFloat(const BigInteger& val) {
		return val.toFloat();
	}
	static double toDouble(const BigInteger& val) {
		return val.toDouble();
	}

	static BigInteger toBigInteger(const vstring& str) {
		return BigInteger(str);
	}
	static BigInteger toBigInteger(dlong value) {
		return BigInteger(value);
	}
	static BigInteger toBigInteger(int value) {
		return BigInteger(value);
	}
	static BigInteger toBigInteger(float value) {
		return BigInteger((int)value);
	}
	static BigInteger toBigInteger(double value) {
		return BigInteger((int)value);
	}
	static vstring toText(const BigInteger& val) {
		return val.toString();
	}

	///////////////////////
	static int toInt(const BigDecimal& val) {
		return val.toInt();
	}
	static dlong toLong(const BigDecimal& val) {
		return val.toLong();
	}
	static float toFloat(const BigDecimal& val) {
		return val.toFloat();
	}
	static double toDouble(const BigDecimal& val) {
		return val.toDouble();
	}
	static BigDecimal toBigDecimal(const vstring& str) {
		return BigDecimal(str);
	}
	static BigDecimal toBigDecimal(int value) {
		return BigDecimal(value);
	}
	static BigDecimal toBigDecimal(dlong value) {
		return BigDecimal(value);
	}
	static BigDecimal toBigDecimal(float value) {
		return BigDecimal(value);
	}
	static BigDecimal toBigDecimal(double value) {
		return BigDecimal(value);
	}
	static BigDecimal toBigDecimal(const BigInteger& value) {
		return BigDecimal(value);
	}

	static vstring toText(const BigDecimal& val) {
		return val.toString();
	}

	static vstring format(const vstring& str, const ObjectList& args);

	static vstring& toText(vstringbuffer& val) {
		return val;
	}

};
VOLANTE_NAMESPACE_END

#endif //__FORMATFUNCTIONS_H__

