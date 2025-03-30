#pragma once

#include "lens.h"

#include <QPointF>

#include <optional>

struct Refraction
{
    double input_angle = 0.0;
    double output_angle = 0.0;
};

// Refraction calculate_refraction(const Lens &lens, const Ray &initial_ray);

struct Ray
{
    QPointF origin;
    double angle;
};

struct Circle
{
    QPointF center;
    double radius;
};

std::optional<double> solveQuadratic(double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return std::nullopt;
    }
    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b + sqrtDiscriminant) / (2 * a);
    double t2 = (-b - sqrtDiscriminant) / (2 * a);

    // We only need the smallest non-negative t
    if (t1 >= 0 && t2 >= 0)
    {
        return std::min(t1, t2);
    }
    else if (t1 >= 0)
    {
        return t1;
    }
    else if (t2 >= 0)
    {
        return t2;
    }
    else
    {
        return std::nullopt;
    }
}

std::optional<QPointF> rayCircleIntersection(const Ray &ray, const Circle &circle, double maxHeight)
{
    double dx = std::cos(ray.angle);
    double dy = std::sin(ray.angle);

    double a = 1.0; // cos^2(angle) + sin^2(angle) = 1
    double b = 2 * ((ray.origin.x() - circle.center.x()) * dx + (ray.origin.y() - circle.center.y()) * dy);
    double c = (ray.origin.x() - circle.center.x()) * (ray.origin.x() - circle.center.x()) +
               (ray.origin.y() - circle.center.y()) * (ray.origin.y() - circle.center.y()) -
               circle.radius * circle.radius;

    auto t = solveQuadratic(a, b, c);

    if (t.has_value())
    {
        QPointF intersection(ray.origin.x() + t.value() * dx, ray.origin.y() + t.value() * dy);
        // Check if the intersection point is within the height of the lens
        if (std::abs(intersection.y()) <= maxHeight / 2)
        {
            return intersection;
        }
    }

    return std::nullopt;
}

std::optional<QPointF> findFirstIntersection(const Ray &ray, const Circle &circle1, const Circle &circle2,
                                             double maxHeight)
{
    auto intersection1 = rayCircleIntersection(ray, circle1, maxHeight);
    auto intersection2 = rayCircleIntersection(ray, circle2, maxHeight);

    if (intersection1 && intersection2)
    {
        double dist1 = std::hypot(intersection1->x() - ray.origin.x(), intersection1->y() - ray.origin.y());
        double dist2 = std::hypot(intersection2->x() - ray.origin.x(), intersection2->y() - ray.origin.y());
        return (dist1 < dist2) ? intersection1 : intersection2;
    }
    else if (intersection1)
    {
        return intersection1;
    }
    else if (intersection2)
    {
        return intersection2;
    }

    return std::nullopt;
}
