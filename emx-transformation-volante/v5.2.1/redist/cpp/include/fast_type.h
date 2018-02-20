// $Id: fastapi.h,v 1.2 2006/02/09 19:14:24 Daniel.May Exp $
//
// FIX Adapted for STreaming (sm) (FAST Protocol (sm)) 
//
// Copyright (c) 2005-2006, Pantor Engineering AB (http://www.pantor.com)
// Copyright (c) 2005-2006, SpryWare LLC (http://www.spryware.com)
// Copyright (c) 2005-2006, FIX Protocol Ltd (http://www.fixprotocol.org)
// All Rights Reserved.
//
// This work is distributed under the W3C® Software License [1] in the
// hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY, SATISFACTORY QUALITY or FITNESS 
// FOR A PARTICULAR PURPOSE.
//
// [1] http://www.w3.org/Consortium/Legal/2002/copyright-software-20021231
// [FPL's Intellectual Property details] http://www.fixprotocol.org/ip
// [FAST Protocol details] http://www.fixprotocol.org/fast
// [FAST Protocol credits] http://fixprotocol.org/fastcredits

#ifndef _fasttype_h_
#define _fasttype_h_ 1

//////////////////////////////////////////////////////////////////////

typedef enum fast_op_t
{
   FAST_OP_NONE = 0,
   FAST_OP_COPY,
   FAST_OP_INCR,
   FAST_OP_DELTA,
}
fast_op_t;

typedef enum fast_type_t
{
   FAST_TYPE_NULL = 0,
   FAST_TYPE_U32,
   FAST_TYPE_I32,
   FAST_TYPE_STR,
}
fast_type_t;

struct fast_tag_type {
	inline fast_tag_type(int id, fast_type_t type, fast_op_t op, int tid) {
		this->id = id;
		this->type = type;
		this->op = op;
		this->tid = tid;
	}
	int id;
	fast_type_t type;
	fast_op_t op;
	int tid;
};

#endif // _fasttype_h_
