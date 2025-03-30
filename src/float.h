#pragma once

#include "lens.h"

inline constexpr double EPS = 1e-5;

bool isEqual(double a, double b);
bool isZero(double value);

double calculateSagitta(double r, double h);
double calculateSagitta1(const Lens &lens);
double calculateSagitta2(const Lens &lens);
