#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <iostream>

#include "IThread.h"

class CWThread : public IThread
{
private:
	HANDLE _thread;
public:
	CWThread(LPVOID parameter, LPTHREAD_START_ROUTINE function, LPDWORD returnValue);
	~CWThread();
	virtual bool		THStart();
	virtual bool		THWait();
	virtual bool		THDestroy();
};

