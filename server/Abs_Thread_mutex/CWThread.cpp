#include "CWThread.h"

CWThread::CWThread(LPVOID parameter, LPTHREAD_START_ROUTINE function, LPDWORD returnValue)
{
	HANDLE thread;
	thread = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            function,       // thread function name
            parameter,          // argument to thread function 
            CREATE_SUSPENDED,   // The thread is created in a suspended state, and does not run until the ResumeThread function is called.
            returnValue);   // returns the thread identifier 
	if (thread == NULL)
	{
		 std::cerr << "[ERROR] Could create this thread" << std::endl;
		 exit(0);
	}
	_thread = thread;
}

bool		CWThread::THStart()
{
	DWORD ret;

	ret = ResumeThread(this->_thread);
	if (ret == -1)
		return (false);
	return (true);
}

bool		CWThread::THWait()
{
	DWORD ret;

	ret = WaitForSingleObject(this->_thread, INFINITE);
	if (ret == WAIT_FAILED)
		return (false);
	return (true);
}

bool		CWThread::THDestroy()
{
	CloseHandle(this->_thread);
	return (true);
}