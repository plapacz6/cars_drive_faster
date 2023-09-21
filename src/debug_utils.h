#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <iostream>
#ifdef PDEBUG_ON
#define PDEBUG(X) std::cerr << X << std::endl;
#else
#define PDEBUG(X) ;
#endif //PDEBUG_ON

#endif // DEBUG_UTILS_H