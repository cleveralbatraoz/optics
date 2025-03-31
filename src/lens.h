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

  private:
    double r1;
    double r2;
    double h;
    double d;
    double n;
};
