// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define EXPORT __declspec(dllexport)
#define FASTCALL __fastcall
#define FUNCCALL __cdecl
#define IMPORT __declspec(dllimport)
#define NAKED __declspec(naked)
#define STDCALL __stdcall

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <windows.h>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <list>
#include <math.h>
#include <process.h>
#include <psapi.h>
#include <shlwapi.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <tlhelp32.h>
#include <valarray>
#include <vector>
#include <winbase.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>

#include "Array Ex.h"

#include "Threads.h"
#include "Xinput.h"

#include "HF2 Xinput.h"

using namespace std;

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "Xinput.lib")

#pragma warning(disable : 4311)
#pragma warning(disable : 4312)

// TODO: reference additional headers your program requires here
