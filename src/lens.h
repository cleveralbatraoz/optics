#pragma once

#include "paraxial_characteristics.h"

#include <QVector>

class Lens
{
  public:
    Lens(double r1, double r2, double h, double d, double n);

    double get_r1() const;
    double get_r2() const;
    double get_d() const;
    double get_h() const;
    double get_n() const;

    ParaxialCharacteristics compute_paraxial_characteristics() const;

    // Метод для расчета гауссовой матрицы
    static QVector<QVector<double>> calculateGaussianMatrix(double r1, double r2, double d, double n);

    // Метод для расчета матрицы преломления
    static QVector<QVector<double>> calculateTransferMatrix(double d);

    // Метод для расчета матрицы преломления
    static QVector<QVector<double>> calculateRefractionMatrix(double r, double mu);
    static QVector<QVector<double>> calculateRefractionMatrixReverse(double r, double mu);

    inline static QVector<QVector<double>> matrixMultiply(const QVector<QVector<double>> &a,
                                                          const QVector<QVector<double>> &b)
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

  private:
    double r1;
    double r2;
    double h;
    double d;
    double n;
};
