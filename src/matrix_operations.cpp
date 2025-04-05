#include "matrix_operations.h"

#include "float.h"

#include <QVector>
#include <QtTypes>

QVector<QVector<double>> calculateTransferMatrix(double d)
{
    return {{1, -d}, {0, 1}};
}

QVector<QVector<double>> calculateRefractionMatrix(double r, double mu)
{
    const double rho = isZero(r) ? 0.0 : 1 / r;
    return {{1, 0}, {rho * (1 - mu), mu}};
}

QVector<QVector<double>> calculateRefractionMatrixReverse(double r, double mu)
{
    const double rho = isZero(r) ? 0.0 : 1 / r;
    return {{1, 0}, {-(rho * (1 - mu)) / mu, 1 / mu}};
}

QVector<QVector<double>> calculateGaussianMatrix(double r1, double r2, double d, double n)
{
    const QVector<QVector<double>> R1 = calculateRefractionMatrix(r1, 1 / n);
    const QVector<QVector<double>> D = calculateTransferMatrix(d);
    const QVector<QVector<double>> R2 = calculateRefractionMatrix(r2, n);
    const QVector<QVector<double>> RD = matrixMultiply(R2, matrixMultiply(D, R1));
    return RD;
}

QVector<QVector<double>> matrixMultiply(const QVector<QVector<double>> &a, const QVector<QVector<double>> &b)
{
    const qsizetype rowsA = a.size();
    const qsizetype colsA = a[0].size();
    const qsizetype colsB = b[0].size();

    QVector<QVector<double>> result(rowsA, QVector<double>(colsB));

    for (qsizetype i = 0; i < rowsA; ++i)
    {
        for (qsizetype j = 0; j < colsB; ++j)
        {
            for (qsizetype k = 0; k < colsA; ++k)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}
