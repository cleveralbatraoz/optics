#pragma once

#include "paraxial_characteristics.h"
#include "ray.h"

#include <QPointF>

struct RefractionResult
{
    QPointF intersection_point1;
    QPointF intersection_point2;
    double exit_angle;
};

class Lens
{
  public:
    Lens(double r1, double r2, double h, double d, double n);

    double get_r1() const;
    double get_r2() const;
    double get_d() const;
    double get_h() const;
    double get_n() const;

    RefractionResult refract(const Ray &ray) const;

    ParaxialCharacteristics compute_paraxial_characteristics() const;

  private:
    double r1;
    double r2;
    double h;
    double d;
    double n;
};
