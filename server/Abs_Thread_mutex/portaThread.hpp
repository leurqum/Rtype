#pragma once

#ifdef __unix__

# include "UThread.hpp"
# include "UMutex.hpp"

// class UMutex;
//  class UThread;

typedef UThread MyThread;
typedef UMutex MyMutex;


//-------------------

#elif defined _WIN32

# include "CWThread.h"
# include "WMutex.h"
//# include "WServerSocket.hpp"

class CWMutex;
class CWThread;

typedef CWThread MyThread;
typedef CWMutex MyMutex;

#endif
