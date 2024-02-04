#ifndef PDEBUG_H
#define PDEBUG_H
#include <iostream>

#define PDEBUG_(X) std::cout << #X << " " << X << std::endl;

#endif // PDEBUG_H