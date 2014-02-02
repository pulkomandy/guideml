#pragma once

static inline int Strnicmp(const char* a, const char* b, int len)
{
	return strncasecmp(a,b, len);
}

