#pragma once

#ifdef __unix__

# include "UThread.hpp"


class UThread;
typedef UThread MyThread;


//-------------------

#elif defined _WIN32

# include "CWThread.h"
# include "WServerSocket.hpp"

class CWThread;
typedef CWThread MyThread;


#endif
