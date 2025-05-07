#ifndef PATH_H
#define PATH_H

#include <vector>
#include "Point.h"

struct Path {
    std::vector<Point> points;
    char symbol;
    
    Path(char _symbol = ' ') : symbol(_symbol) {}
};

#endif // PATH_H
