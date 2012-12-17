#include <windows.h>
#include <stdio.h>
#include "CWThread.h"
#include "WMutex.h"
#include <vector>
#define THREADCOUNT 2




DWORD WINAPI WriteToDatabase( LPVOID );
IMutex *ghMutex;

int main( void )
{
    std::vector<IThread*>aThread;
    DWORD ThreadID;
    int i;
	
    // Create a mutex with no initial owner
	ghMutex = new CWMutex();
    if (ghMutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads

    for( i=0; i < THREADCOUNT; i++ )
    {
		CWThread *th = new CWThread(NULL, (LPTHREAD_START_ROUTINE) WriteToDatabase, &ThreadID);
		aThread.push_back(th);
                      // receive thread identifier
		th->THSart();
        if( aThread[i] == NULL )
        {
            printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }

    // Wait for all threads to terminate
	for( i=0; i < THREADCOUNT; i++ )
    {
		aThread[i]->THWait();
	}

    // Close thread and mutex handles

    for( i=0; i < THREADCOUNT; i++ )
		aThread[i]->THDestroy();
	ghMutex->MDestroy();
	system("pause");
    return 0;
}

DWORD WINAPI WriteToDatabase( LPVOID lpParam )
{ 
    // lpParam not used in this example
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwCount=0, dwWaitResult; 

    // Request ownership of mutex.

    while( dwCount < 20 )
    { 
		dwWaitResult = ghMutex->MTryLock();
 
        if (dwWaitResult == true)
		{
        
            // TODO: Write to the database
            printf("Thread %d writing to database...\n", 
                    GetCurrentThreadId());
            dwCount++;
			if (ghMutex->MUnLock() == false) 
            { 
                // Handle error.
            } 
         } 
		else
            return FALSE; 
        }
    return TRUE; 
}