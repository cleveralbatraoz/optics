#include "lens.h"

#include "float.h"
#include "matrix_operations.h"
#include "paraxial_characteristics.h"

#include <QVector>

Lens::Lens(double r1, double r2, double h, double d, double n) : r1(r1), r2(r2), h(h), d(d), n(n)
{
}

double Lens::get_r1() const
{
    return r1;
}

double Lens::get_r2() const
{
    return r2;
}

double Lens::get_d() const
{
    return d;
}

double Lens::get_h() const
{
    return h;
}

double Lens::get_n() const
{
    return n;
}

ParaxialCharacteristics Lens::compute_paraxial_characteristics() const
{
    const QVector<QVector<double>> G = calculateGaussianMatrix(r1, r2, d, n);

    // Элементы матрицы G
    double A = G[0][0];
    double C = G[1][0];
    double D = G[1][1];

    // Расчет параметров
    double f_back = 1 / C;
    double f_front = -f_back;
    double Sf_back = A / C;
    double Sf_front = (-D) / C;
    double Sh_front = Sf_front + f_back;
    double Sh_back = Sf_back - f_back;

    return {.f = {f_front, f_back}, .sf = {Sf_front, Sf_back}, .sh = {Sh_front, Sh_back}};
}
