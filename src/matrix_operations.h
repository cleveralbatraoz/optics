#pragma once

#include <QVector>

QVector<QVector<double>> calculateGaussianMatrix(double r1, double r2, double d, double n);

QVector<QVector<double>> calculateTransferMatrix(double d);

QVector<QVector<double>> calculateRefractionMatrix(double r, double mu);
QVector<QVector<double>> calculateRefractionMatrixReverse(double r, double mu);

QVector<QVector<double>> matrixMultiply(const QVector<QVector<double>> &a, const QVector<QVector<double>> &b);
