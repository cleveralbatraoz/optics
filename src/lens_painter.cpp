#include "lens_painter.h"

#include "float.h"
#include "lens.h"

#include <QLineF>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QVector>
#include <QWidget>

#include <algorithm>
#include <cmath>
#include <numbers>

LensPainter::LensPainter(const Lens &lens, const Ray &ray, QWidget *parent) : QWidget(parent), lens(lens), ray(ray)
{
    setFixedSize(800, 800);
}

void LensPainter::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    const QPainterPath lens_path = compose_lens_path();

    const QRectF pathRect = lens_path.boundingRect();
    const QRect widgetRect = rect();
    const QPointF widgetCenter = widgetRect.center();

    const double scale_x = widgetRect.width() / pathRect.width();
    const double scale_y = widgetRect.height() / pathRect.height();
    const double scale = std::min(scale_x, scale_y) / 2;

    painter.translate(widgetCenter);
    painter.scale(scale, scale);

    const double infinity = 200000.0;
    const double enter_angle = qDegreesToRadians(ray.alpha);

    const RefractionResult refraction_result = lens.refract(ray);

    const QPointF ray1_vector(std::cos(enter_angle), std::sin(enter_angle));
    const QPointF ray3_vector(std::cos(refraction_result.exit_angle), std::sin(refraction_result.exit_angle));

    const QPointF start_point = refraction_result.intersection_point1 - ray1_vector * infinity;
    const QPointF end_point = refraction_result.intersection_point2 + ray3_vector * infinity;

    const QLineF line1(start_point, refraction_result.intersection_point1);
    const QLineF line2(refraction_result.intersection_point1, refraction_result.intersection_point2);
    const QLineF line3(refraction_result.intersection_point2, end_point);

    draw_lens(painter, lens_path);
    draw_lines(painter, line1, line2, line3);
}

QPainterPath LensPainter::compose_lens_path()
{
    QPainterPath path;

    const double r1 = lens.get_r1();
    const double r2 = lens.get_r2();
    const double h = lens.get_h();
    const double d = lens.get_d();

    const double arrow1 = calculateSagitta1(lens);
    const double arrow2 = calculateSagitta2(lens);

    path.moveTo(arrow1, -h);

    if (isZero(r1))
    {
        path.lineTo(path.currentPosition() + QPointF(0.0, 2 * h));
    }
    else
    {
        double dAngle = asin(h / r1) * 180 / std::numbers::pi;
        if (r1 > 0)
        {
            path.arcTo(0, -r1, r1 * 2, r1 * 2, 180 - dAngle, dAngle * 2);
        }
        else
        {
            path.arcTo(2 * r1, r1, -r1 * 2, -r1 * 2, -dAngle, dAngle * 2);
        }
    }

    path.lineTo(path.currentPosition() + QPointF(d + arrow2 - arrow1, 0.0));

    if (isZero(r2))
    {
        path.lineTo(path.currentPosition() - QPointF(0.0, 2 * h));
    }
    else
    {
        double dAngle = asin(h / r2) * 180 / std::numbers::pi;
        if (r2 > 0)
        {
            path.arcTo(d, -r2, r2 * 2, r2 * 2, 180 + dAngle, -dAngle * 2);
        }
        else
        {
            path.arcTo(d + 2 * r2, r2, -r2 * 2, -r2 * 2, dAngle, -dAngle * 2);
        }
    }

    path.closeSubpath();

    return path;
}

void LensPainter::draw_lens(QPainter &painter, const QPainterPath &lens_path)
{
    QPen pen = obtain_default_pen();

    painter.fillPath(lens_path, Qt::gray);

    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawPath(lens_path);
}

void LensPainter::draw_lines(QPainter &painter, const QLineF &line1, const QLineF &line2, const QLineF &line3)
{
    QPen pen = obtain_default_pen();
    painter.setPen(pen);

    pen.setColor(Qt::yellow);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(line1);

    pen.setColor(Qt::blue);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawLine(line2);

    pen.setColor(Qt::yellow);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(line3);
}

QPen LensPainter::obtain_default_pen()
{
    QPen pen;

    pen.setWidthF(0.35);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    return pen;
}
