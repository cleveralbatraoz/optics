#pragma once

#include <QVector>

// Метод для расчета гауссовой матрицы
QVector<QVector<double>> calculateGaussianMatrix(double r1, double r2, double d, double n);

// Метод для расчета матрицы преломления
QVector<QVector<double>> calculateTransferMatrix(double d);

// Метод для расчета матрицы преломления
QVector<QVector<double>> calculateRefractionMatrix(double r, double mu);
QVector<QVector<double>> calculateRefractionMatrixReverse(double r, double mu);

QVector<QVector<double>> matrixMultiply(const QVector<QVector<double>> &a, const QVector<QVector<double>> &b);
