#include "lens.h"

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

QVector<QVector<double>> Lens::calculateTransferMatrix(double d)
{
    return {{1, -d}, {0, 1}};
}

QVector<QVector<double>> Lens::calculateRefractionMatrix(double r, double mu)
{
    double rho = 1 / r;
    return {{1, 0}, {rho * (1 - mu), mu}};
}

QVector<QVector<double>> Lens::calculateRefractionMatrixReverse(double r, double mu)
{
    double rho = 1 / r;
    return {{1, 0}, {-(rho * (1 - mu)) / mu, 1 / mu}};
}

QVector<QVector<double>> Lens::calculateGaussianMatrix(double r1, double r2, double d, double n)
{
    // Матрица преломления на первой поверхности
    QVector<QVector<double>> R1 = calculateRefractionMatrix(r1, 1 / n);

    // Матрица переноса между поверхностями
    QVector<QVector<double>> D = calculateTransferMatrix(d);

    // Матрица преломления на второй поверхности
    QVector<QVector<double>> R2 = calculateRefractionMatrix(r2, n);

    // Умножение матриц в правильном порядке: G = R2 * D * R1
    QVector<QVector<double>> RD = matrixMultiply(R2, matrixMultiply(D, R1));

    return RD;
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
