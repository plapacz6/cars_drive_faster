#ifndef PDEBUG_H
#define PDEBUG_H
#include <iostream>
#include <cassert>

#ifdef DEBUG_MSG
#define PDEBUG_(X) std::cout << #X << " " << X << std::endl;
#define PMDEBUG(M) std::cout << #M << " " << M << std::endl;
#define PMADEBUG(M, A) std::cout << #M << ": " << #A << " " << A << std::endl;
#else
#define PDEBUG_(X) ;
#define PMDEBUG(M) ;
#define PMADEBUG(M, A) ;
#endif //DEBUG_MSG
#endif // PDEBUG_H