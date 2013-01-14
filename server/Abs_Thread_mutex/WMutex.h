#pragma once
#include "IMutex.h"
#include "windows.h"
#include <iostream>

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

