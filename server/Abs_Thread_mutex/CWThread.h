#pragma once
#include "IThread.h"
#include <windows.h>
#include <string>
#include <iostream>
class CWThread : public IThread
{
private:
	HANDLE _thread;
public:
	CWThread(LPVOID parameter, LPTHREAD_START_ROUTINE function, LPDWORD returnValue);
	~CWThread();
	virtual bool		THSart();
	virtual bool		THWait();
	virtual bool		THDestroy();
};

