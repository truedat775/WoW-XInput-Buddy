#include "stdafx.h"

#define	XINPUT			1

typedef struct Thread_t
{
	HANDLE Handle;
	DWORD ID;
} THREAD, *LPTHREAD;

BOOL STDCALL Threads(LPVOID Parameter);
HANDLE MakeThread(LPVOID Process, LPVOID Parameter);
VOID DestroyThread(HANDLE Thread, DWORD Parameter, DWORD MaxWaitTime);

VOID CreateXinputThreads();
VOID DestroyXinputThreads();