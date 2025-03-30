#include "float.h"

#include <cmath>

bool isEqual(double a, double b)
{
    return fabs(a - b) < EPS;
}

bool isZero(double value)
{
    return isEqual(value, 0.0);
}
