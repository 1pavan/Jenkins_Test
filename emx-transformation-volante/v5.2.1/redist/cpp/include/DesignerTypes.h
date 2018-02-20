#ifndef __DESIGNERTYPES_H__
#define __DESIGNERTYPES_H__

VOLANTE_NAMESPACE_BEGIN

/*
*  DesignerTypes.h
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

#define DESIGNER_INT_TYPE "Integer"
#define DESIGNER_FLOAT_TYPE "Float"
#define DESIGNER_DOUBLE_TYPE "Double"
#define DESIGNER_DATE_TIME_TYPE  "DateTime"
#define DESIGNER_DATE_ONLY_TYPE  "DateOnly"
#define DESIGNER_TIME_ONLY_TYPE  "TimeOnly"
#define DESIGNER_ISO_DATE_TIME_TYPE  "ISODateTime"
#define DESIGNER_ISO_DATE_TYPE  "ISODate"
#define DESIGNER_ISO_TIME_TYPE  "ISOTime"
#define DESIGNER_STRING_TYPE  "String"
#define DESIGNER_CHAR_TYPE  "Character"
#define DESIGNER_SECTION_TYPE  "Section"
#define DESIGNER_DATAOBJECT_TYPE  "DataObject"
#define DESIGNER_LONG_TYPE  "Long"
#define DESIGNER_BOOLEAN_TYPE "Boolean"
#define DESIGNER_BINARY_TYPE "Binary"
#define DESIGNER_BIG_INTEGER_TYPE "BigInteger"
#define DESIGNER_BIG_DECIMAL_TYPE "BigDecimal"

class VOLANTE_EXPORT DesignerTypes {
public:
    static vstringliteral INT_TYPE;
    static vstringliteral FLOAT_TYPE;
    static vstringliteral DOUBLE_TYPE;
    static vstringliteral DATE_TIME_TYPE;
    static vstringliteral DATE_ONLY_TYPE;
    static vstringliteral TIME_ONLY_TYPE;
    static vstringliteral ISO_DATE_TIME_TYPE;
    static vstringliteral ISO_DATE_TYPE;
    static vstringliteral ISO_TIME_TYPE;
    static vstringliteral STRING_TYPE;
    static vstringliteral CHAR_TYPE;
    static vstringliteral SECTION_TYPE;
    static vstringliteral DATAOBJECT_TYPE;
    static vstringliteral LONG_TYPE;
    static vstringliteral BOOLEAN_TYPE;
    static vstringliteral BINARY_TYPE;
    static vstringliteral RAW_MESSAGE_TYPE;
    static vstringliteral BIG_INTEGER_TYPE;
    static vstringliteral BIG_DECIMAL_TYPE;
};

VOLANTE_NAMESPACE_END


#endif //__DESIGNERTYPES_H__

