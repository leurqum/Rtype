#include "WMutex.h"


CWMutex::CWMutex()
{
	HANDLE mutex;
	mutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex
	if (mutex == NULL)
	{
		 std::cerr << "[ERROR] Could create this mutex" << std::endl;
		 exit(0);
	}
	_mutex = mutex;
}

bool		CWMutex::MUnlock()
{
	if (!ReleaseMutex(this->_mutex))
		return (false);
	return (true);
}

bool		CWMutex::MLock()
{
	return (true);
}

bool		CWMutex::MDestroy()
{
	CloseHandle(this->_mutex);
	return (true);
}

bool		CWMutex::MTryLock()
{
	 DWORD dwWaitResult = WaitForSingleObject( 
            this->_mutex,    // handle to mutex
            INFINITE);  // no time-out interval
	if (dwWaitResult == WAIT_OBJECT_0)
		return (true);
	return (false);
}
