#pragma once

#ifdef __unix__

# include "UThread.hpp"


class UThread;
typedef UThread MyThread;


//-------------------

#elif defined _WIN32

# include "CWThread.hpp"
# include "WServerSocket.hpp"

class CWThread;
typedef CWThread MyThread;


#endif
