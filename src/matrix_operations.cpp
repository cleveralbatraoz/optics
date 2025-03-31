#include "matrix_operations.h"

#include "float.h"

#include <QVector>

QVector<QVector<double>> calculateTransferMatrix(double d)
{
    return {{1, -d}, {0, 1}};
}

QVector<QVector<double>> calculateRefractionMatrix(double r, double mu)
{
    double rho = isZero(r) ? 0.0 : 1 / r;
    return {{1, 0}, {rho * (1 - mu), mu}};
}

QVector<QVector<double>> calculateRefractionMatrixReverse(double r, double mu)
{
    double rho = isZero(r) ? 0.0 : 1 / r;
    return {{1, 0}, {-(rho * (1 - mu)) / mu, 1 / mu}};
}

QVector<QVector<double>> calculateGaussianMatrix(double r1, double r2, double d, double n)
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
