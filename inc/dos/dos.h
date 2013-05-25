#pragma once

#include <proto/exec.h>

/* Returned by ReadItem() */
#define ITEM_EQUAL    -2
#define ITEM_ERROR    -1
#define ITEM_NOTHING   0
#define ITEM_UNQUOTED  1
#define ITEM_QUOTED    2

// dos_intern.h
#define RDAF_ALLOCATED_BY_READARGS (1L << 31)
struct DAList
{
	STRPTR *ArgBuf;
	UBYTE  *StrBuf;
	STRPTR *MultVec;
	BOOL    FreeRDA;
};
