#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <iostream>

#include "IMutex.h"

class CWMutex : public IMutex
{
private:
	HANDLE _mutex;
	DWORD _dwWaitResult;
public:
	CWMutex();
	virtual bool		MUnLock();
	virtual bool		MLock();
	virtual bool		MDestroy();
	virtual bool		MTryLock();
};

