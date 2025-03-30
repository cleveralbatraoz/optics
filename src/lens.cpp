#include "lens.h"

#include "paraxial_characteristics.h"

#include <QVector>
#include <QtTypes> // qsizetype

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

QVector<QVector<double>> matrixMultiply(const QVector<QVector<double>> &a, const QVector<QVector<double>> &b)
{
    int rowsA = a.size();
    int colsA = a[0].size();
    int colsB = b[0].size();

    QVector<QVector<double>> result(rowsA, QVector<double>(colsB, 0));

    for (int i = 0; i < rowsA; ++i)
    {
        for (int j = 0; j < colsB; ++j)
        {
            for (int k = 0; k < colsA; ++k)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

QVector<QVector<double>> calculateTransferMatrix(double d)
{
    return {{1, -d}, {0, 1}};
}

// Метод для расчета матрицы преломления
QVector<QVector<double>> calculateRefractionMatrix(double r, double mu)
{
    double rho = 1 / r;
    return {{1, 0}, {rho * (1 - mu), mu}};
}

// Метод для расчета гауссовой матрицы
QVector<QVector<double>> calculateGaussianMatrix(const Lens &lens)
{
    const double r1 = lens.get_r1();
    const double r2 = lens.get_r2();
    const double d = lens.get_d();
    const double n = lens.get_n();

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
    const QVector<QVector<double>> G = calculateGaussianMatrix(*this);

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
