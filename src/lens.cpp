#include "lens.h"

#include "paraxial_characteristics.h"

#include <QVector>

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

ParaxialCharacteristics Lens::compute_paraxial_characteristics() const
{
    const QVector<double> radiuses = {0.0, r1, r2};
    const QVector<double> distances = {0.0, d, 0.0};
    const QVector<double> refractive_index = {1.0, n, 1.0};

    QVector<QVector<double>> transform = {
        {1.0, 0.0},
        {0.0, 1.0},
    };

    for (qsizetype i = 1; i < refractive_index.size(); ++i)
    {
        transform[0][0] -= distances[i - 1] * transform[1][0];
        transform[0][1] -= distances[i - 1] * transform[1][1];

        const double mu = refractive_index[i - 1] / refractive_index[i];
        const double surface_curvature = (radiuses[i] == 0) ? 0.0 : (1.0 / radiuses[i]);
        const double alpha = surface_curvature * (1.0 - mu);

        transform[1][0] = transform[1][0] * mu + alpha * transform[0][0];
        transform[1][1] = transform[1][1] * mu + alpha * transform[0][1];
    }

    return compute_paraxial_characteristics_from_transform_matrix(transform);
}

ParaxialCharacteristics Lens::compute_paraxial_characteristics_from_transform_matrix(
    const QVector<QVector<double>> &transform)
{
    ParaxialCharacteristics paraxial_characteristics;

    paraxial_characteristics.f.front = transform[0][1] - (transform[0][0] * transform[1][1]) / transform[1][0];
    paraxial_characteristics.f.back = 1.0 / transform[1][0];

    paraxial_characteristics.sf.front = -transform[1][1] / transform[1][0];
    paraxial_characteristics.sf.back = transform[0][0] / transform[1][0];

    paraxial_characteristics.sh.front = paraxial_characteristics.sf.front - paraxial_characteristics.f.front;
    paraxial_characteristics.sh.back = paraxial_characteristics.sf.back - paraxial_characteristics.f.back;

    return paraxial_characteristics;
}
