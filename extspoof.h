#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <tchar.h>

#include <Windows.h> 
#define AUTHOR "vivid"

#ifndef _UNICODE
	#error Only unicode is supported
#endif

#ifndef WIN32
	#error Target Windoze to compile __FILE__
#endif

const TCHAR tzUsage[] = {
	TEXT("extspoof by ") TEXT(AUTHOR) TEXT("\n\n")
	TEXT("Usage: extspoof [in] [ext]\n")
	TEXT("\t-o         : forcibly overwrite output if it already exists") 
};