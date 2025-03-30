#include "float.h"

#include "lens.h"

#include <QVector>

#include <cmath>

bool isEqual(double a, double b)
{
    return fabs(a - b) < EPS;
}

bool isZero(double value)
{
    return isEqual(value, 0.0);
}

double calculateSagitta(double r, double h)
{
    double arrow = 0.0;

    if (!isZero(r))
    {
        arrow = fabs(r) - sqrt(r * r - h * h);
    }
    if (r < 0.0)
    {
        arrow = -arrow;
    }

    return arrow;
}

double calculateSagitta1(const Lens &lens)
{
    return calculateSagitta(lens.get_r1(), lens.get_h());
}

double calculateSagitta2(const Lens &lens)
{
    return calculateSagitta(lens.get_r2(), lens.get_h());
}
