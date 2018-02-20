var today = new Date();
var day = today.getDate();
var month = today.getMonth();
var year = y2k(today.getFullYear());
var currentFldName = "";
var currentFormName = "";
var currentDateFormat = "yyyyMMdd";
var currentDate;

function padout(number) { return (number < 10) ? '0' + number :  ''+number; }

function y2k(number) { 
	if (number < 100) {
		if (number < 70) {
			return number + 2000 ;
		}
		else {
			return number + 1900; 
		}
	}
	else {
		return number;
	}
}

function newWindow2(formName, fldName, format) {
	//date format should not be wrong
    currentDateFormat = format;
    currentFldName = fldName;
    currentFormName = formName;
    var currentFldValue = document.forms[currentFormName].elements[currentFldName].value;
    if (currentFldValue == "") {
		currentDate = new Date();
        currentDate = new Date(currentDate.getFullYear(), currentDate.getMonth(), currentDate.getDate());
    }
    else {
		currentDate = parseDate(currentFldValue, currentDateFormat);
    }
    day = currentDate.getDate();
    month = currentDate.getMonth();
    year = y2k(currentDate.getFullYear());
    var mywindow=open('calendar.html','myForm','resizable=no,width=200,height=200,top=300');
    mywindow.location.href = 'calendar.html';
    mywindow.opener = self;
    if (mywindow.open){
		mywindow.focus();
    }
}

function newWindow(formName, fldName, format) {
    if(format == null) {
        //format = "yyyy-MM-dd HH:mm:ss.SSS";
        format = "yyyyMMdd";
    }
    currentDateFormat = format;
    newWindow2(formName, fldName, format);
}

function displaydate() {
	var date = new Date(year, month, day, currentDate.getHours(), currentDate.getMinutes(), currentDate.getSeconds(), currentDate.getMilliseconds());	
	document.forms[currentFormName].elements[currentFldName].value = formatDate(date, currentDateFormat);
}
function clearDate() {
	document.forms[currentFormName].elements[currentFldName].value = "";
}


////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//functions to parse and format dates

var ab_day_nm = new Array("Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat");

var day_nm =
        new Array("Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday");

var ab_month_nm =
        new Array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");

var month_nm =
        new Array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");


function getMonth3Char(month3Str) {
    for (var i = 0; i < 12; ++i) {
        if (ab_month_nm[i] == month3Str) {
            return i;
        }
    }
    return -1;
}

function getMonthFull(monthNStr, start) {
    monthNStr = monthNStr.substring(start);
    for (var i = 0; i < 12; ++i) {
        if (monthNStr == month_nm[i]) {
            return i;
        }
    }
    return -1;
}

function appendPaddedInt(str, length, value) {
    var s = value.toString();
    var actualStrLength = s.length;
    var toPad = length - actualStrLength;
    if (toPad > 0) {
        while (toPad > 0) {
            str += ('0');
            --toPad;
        }
    }
    return str + s;
}


function formatDate(time, format) {
    var p = ""
    format += '\0';
    var fmtIndex = 0;
    var tm_year = time.getFullYear();
    var tm_mon = time.getMonth();
    var tm_mday = time.getDate();
    var tm_hour = time.getHours();
    var tm_min = time.getMinutes();
    var tm_sec = time.getSeconds();
    var tm_msec = time.getMilliseconds();
    var len = format.length;
    while (fmtIndex < len) {
        var c = format.charAt(fmtIndex++);
        switch (c) {
            case 'y': {
                var ycount = 1;
                while (format.charAt(fmtIndex) == 'y') {
                    ++ycount;
                    fmtIndex++;
                }
                if (ycount == 4) {
                    if (tm_year >= 10000 || tm_year < 0) {
                        p = appendPaddedInt(p, 5, tm_year);
                    }
                    else {
                        p = appendPaddedInt(p, 4, tm_year);
                    }
                }
                else {
                    p = appendPaddedInt(p, 2, tm_year % 100);
                }
            }
                continue;
            case'M': {
                var mcount = 1;
                while (format.charAt(fmtIndex) == 'M') {
                    ++mcount;
                    fmtIndex++;
                }
                if (mcount <= 2) {
                    p = appendPaddedInt(p, 2, tm_mon + 1);
                }
                else if (mcount == 3) {
                    var r = ab_month_nm[tm_mon];
                    p += (r);
                }
                else {
                    var r = month_nm[tm_mon];
                    p += r;
                }
            }
                continue;
            case'd': {
                var dcount = 1;
                while (format.charAt(fmtIndex) == 'd') {
                    ++dcount;
                    fmtIndex++;
                }
                //vstring format = "%" + ::toString(dCount);
                p = appendPaddedInt(p, 2, tm_mday);
            }
                continue;
            case'H': {
                var hcount = 1;
                while (format.charAt(fmtIndex) == 'H') {
                    ++hcount;
                    fmtIndex++;
                }
                p = appendPaddedInt(p, 2, tm_hour);
            }
                continue;
            case'm': {
                var mcount = 1;
                while (format.charAt(fmtIndex) == 'm') {
                    ++mcount;
                    fmtIndex++;
                }
                p = appendPaddedInt(p, 2, tm_min);
            }
                continue;
            case's': {
                var scount = 1;
                while (format.charAt(fmtIndex) == 's') {
                    ++scount;
                    fmtIndex++;
                }
                p = appendPaddedInt(p, 2, tm_sec);
            }
                continue;
            case'S': {
                // millis
                var scount = 1;
                while (format.charAt(fmtIndex) == 'S') {
                    ++scount;
                    fmtIndex++;
                }
                p = appendPaddedInt(p, 3, tm_msec);
            }
                continue;
            default:
                if (c != '\0') {
                    p += c;
                }
        }
    }
    return p.toString();
}


function ischardigit(c) {
    return c >= '0' && c <= '9';
}

function toInt(ptr, startIndex, length) {
    if (ptr.length - startIndex < length) {
        throw "Date parsing error";
    }
    var eptr = ptr.substring(startIndex, startIndex + length);
    return parseInt(eptr);
}

function parseDate(dateStr, format) {
    format += '\0';
    var tm_year = 0;
    var tm_mon = 0;
    var tm_mday = 0;
    var tm_hour = 0;
    var tm_min = 0;
    var tm_sec = 0;
    var tm_msec = 0;
    var fmtIndex = 0;
    var inputIndex = 0;
    while (fmtIndex < format.length && inputIndex < dateStr.length) {
        var c = format.charAt(fmtIndex++);
        switch (c) {
            case'y': {
                var ycount = 1;
                while (format.charAt(fmtIndex) == 'y') {
                    ++ycount;
                    fmtIndex++;
                }
                if (ycount >= 4) {
                    tm_year = toInt(dateStr, inputIndex, 4);
                    inputIndex += 4;
                }
                else if (ycount < 2) {
                    throw ("Illegal year pattern in '" + (format) + "'. At least 2 y's expected.");
                }
                else if (ycount == 3 || ycount > 4) {
                    throw ("Illegal year pattern in '" + (format) + "'. Only patterns 'yy' and 'yyyy' are supported.");
                }
                else {
                    var year = toInt(dateStr, inputIndex, 2);
                    if (year < 70) {
                        year += 2000;
                    }
                    else {
                        year += 1900;
                    }
                    tm_year = year;
                    inputIndex += 2;
                }
            }
                break;
            case'M': {
                var mcount = 1;
                while (format.charAt(fmtIndex) == 'M') {
                    ++mcount;
                    fmtIndex++;
                }
                if (mcount == 2) {
                    tm_mon = toInt(dateStr, inputIndex, 2) - 1;
                    inputIndex += 2;
                }
                else if (mcount < 2) {
                    throw ("Illegal month pattern in '" + (format) + "'. At least 2 M's expected.");
                }
                else if (mcount == 3) {
                    var month_index = getMonth3Char(dateStr.substring(inputIndex, inputIndex + 3));
                    if (month_index == -1) {
                        throw ("Error parsing month part of date string, expected pattern " + (format) + " found " + dateStr);
                    }
                    tm_mon = month_index;
                    inputIndex += 3;
                }
                else {
                    var month_index = getMonthFull(dateStr, inputIndex);
                    if (month_index == -1) {
                        throw ("Error parsing month part of date string, expected pattern " + (format) + " found " + dateStr);
                    }
                    tm_mon = month_index;
                    inputIndex += (month_nm[month_index]).length();
                }
            }
                break;
            case'd': {
                var dcount = 1;
                while (format.charAt(fmtIndex) == 'd') {
                    ++dcount;
                    fmtIndex++;
                }
                if (dcount == 2) {
                    tm_mday = toInt(dateStr, inputIndex, 2);
                    inputIndex += 2;
                }
                else {
                    throw ("Illegal date pattern in '" + (format) + "'. Only pattern 'dd' is supported.");
                }
                //vstring format = "%" + ::toString(dCount);
            }
                break;
            case'H': {
                var hcount = 1;
                while (format.charAt(fmtIndex) == 'H') {
                    ++hcount;
                    fmtIndex++;
                }
                if (hcount == 2) {
                    tm_hour = toInt(dateStr, inputIndex, 2);
                    inputIndex += 2;
                }
                else {
                    throw ("Illegal hour pattern in '" + (format) + "'. Only pattern 'HH' is supported.");
                }
            }
                break;
            case'm': {
                var mcount = 1;
                while (format.charAt(fmtIndex) == 'm') {
                    ++mcount;
                    fmtIndex++;
                }
                if (mcount == 2) {
                    tm_min = toInt(dateStr, inputIndex, 2);
                    inputIndex += 2;

                }
                else {
                    throw ("Illegal minute pattern in '" + (format) + "'. Only pattern 'mm' is supported.");
                }
            }
                break;
            case'S': {
                var scount = 1;
                while (format.charAt(fmtIndex) == 'S') {
                    ++scount;
                    fmtIndex++;
                }
                if (scount > 3) {
                    throw ("Illegal milli-seconds pattern in '" + (format) + "'. Only pattern 'SSS' is supported.");
                }
                tm_msec = toInt(dateStr, inputIndex, 3);
                inputIndex += 3;
            }
                break;
            case's': {
                var scount = 1;
                while (format.charAt(fmtIndex) == 's') {
                    ++scount;
                    fmtIndex++;
                }
                if (scount == 2) {
                    tm_sec = toInt(dateStr, inputIndex, 2);
                    inputIndex += 2;
                }
                else {
                    throw "Illegal seconds pattern in '" + (format) + "'. Only pattern 'ss' is supported.";
                }
            }
                break;
            default:
                if (c == '\0') {
                    continue;
                }
                if (c == dateStr.charAt(inputIndex)) {
                    ++inputIndex;
                }
                else {
                    throw ("Error parsing date string, expected pattern '" + (format) + "' found '" + dateStr + "'");
                }
        }
    }
    if (inputIndex != dateStr.length) {
        //Ignore addtional character
        //throw ("Additional characters at the end of date string, expected pattern '" + (format) + "' found '" + dateStr + "'");
    }
    var date = new Date(tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec, tm_msec);
    return date;
}

