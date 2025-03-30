#include "ray.h"

#include <QPointF>
#include <QtMath>

#include <optional>

Refraction calculate_refraction(const Lens &lens, const Ray &initial_ray)
{
    const double input_angle = initial_ray.angle * lens.get_n();
    const double output_angle = input_angle * lens.get_n();
    return {input_angle, output_angle};
}
