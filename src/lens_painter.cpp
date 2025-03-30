#include "lens_painter.h"

#include "float.h"
#include "lens.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
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

    QPen pen;
    pen.setColor(Qt::yellow);        // Set the color of the line
    pen.setWidthF(0.35);             // Set the width of the line
    pen.setStyle(Qt::SolidLine);     // Set the style of the line (e.g., solid, dashed, dotted)
    pen.setCapStyle(Qt::RoundCap);   // Set the cap style for the endpoints
    pen.setJoinStyle(Qt::RoundJoin); // Set the join style for line joins

    // Set the painter's pen
    painter.setPen(pen);

    const QPainterPath path = composePainterPath();

    const QRectF pathRect = path.boundingRect();
    const QRect widgetRect = rect();
    const QPointF widgetCenter = widgetRect.center();

    const double scaleX = widgetRect.width() / pathRect.width();
    const double scaleY = widgetRect.height() / pathRect.height();
    const double scale = std::min(scaleX, scaleY) / 2;

    painter.translate(widgetCenter);
    painter.scale(scale, scale);

    const double arrow1 = calculateSagitta(lens.get_r1(), ray.h);
    const QPointF intersection_point(arrow1, -ray.h);

    const double length = 200000.0;

    const double angle = qDegreesToRadians(ray.alpha);
    const QPointF end_point = intersection_point - QPointF(std::cos(angle) * length, std::sin(angle) * length);
    const QLineF line(intersection_point, end_point);
    painter.drawLine(line);

    const double r1 = lens.get_r1();
    const double r2 = lens.get_r2();
    const double n = lens.get_n();
    const double mu = 1 / n;
    const double d = lens.get_d();

    const QVector<QVector<double>> refraction = Lens::calculateRefractionMatrix(r1, mu);
    const QVector<QVector<double>> transfer = Lens::calculateTransferMatrix(d);

    const QVector<QVector<double>> ray_matrix1 = {{ray.h}, {angle}};
    const QVector<QVector<double>> ray_matrix2 = Lens::matrixMultiply(refraction, ray_matrix1);
    const QVector<QVector<double>> ray_matrix3 = Lens::matrixMultiply(transfer, ray_matrix2);

    const double arrow2 = calculateSagitta(lens.get_r2(), -ray_matrix3[0][0]);
    const QPointF intersection_point2(intersection_point.x() + d + arrow2 - arrow1, -ray_matrix3[0][0]);

    pen.setColor(Qt::red);
    painter.setPen(pen);

    painter.drawLine(QLineF(intersection_point, intersection_point2));

    const QVector<QVector<double>> refraction2 = Lens::calculateRefractionMatrixReverse(r2, mu);
    const QVector<QVector<double>> ray_matrix4 = Lens::matrixMultiply(refraction2, ray_matrix3);
    // const QVector<QVector<double>> transfer2 = Lens::calculateTransferMatrix(length);
    // const QVector<QVector<double>> ray_matrix5 = Lens::matrixMultiply(transfer2, ray_matrix4);

    const QPointF end_point2 =
        intersection_point2 + QPointF(std::cos(ray_matrix4[1][0]) * length, std::sin(ray_matrix4[1][0]) * length);

    // const QPointF intersection_point3(intersection_point2.x() + length, -ray_matrix5[0][0]); // :D

    pen.setColor(Qt::green);
    painter.setPen(pen);

    painter.drawLine(intersection_point2, end_point2);

    pen.setColor(Qt::blue);
    painter.setPen(pen);

    painter.drawPath(path);
}

QPainterPath LensPainter::composePainterPath()
{
    QPainterPath path;

    const double r1 = lens.get_r1();
    const double r2 = lens.get_r2();
    const double h = lens.get_h();
    const double d = lens.get_d();

    // Вычисляем стрелку прогиба поверхностей

    const double arrow1 = calculateSagitta1(lens);
    const double arrow2 = calculateSagitta2(lens);

    // Первая точка контура - верхняя точка поверхности
    path.moveTo(arrow1, -h);

    if (isZero(r1))
    {
        path.lineTo(path.currentPosition() + QPointF(0.0, 2 * h));
    }
    else
    {
        // Рисуем 1ю поверхность (сверху вниз)
        double dAngle = asin(h / r1) * 180 / std::numbers::pi; // угол между осью и крайней точкой поверхности
        if (r1 > 0)
        {
            path.arcTo(0, -r1, r1 * 2, r1 * 2, 180 - dAngle, dAngle * 2);
        }
        else
        {
            path.arcTo(2 * r1, r1, -r1 * 2, -r1 * 2, -dAngle, dAngle * 2);
        }
    }

    // Добавляем нижнюю линию между поверхностями
    path.lineTo(path.currentPosition() + QPointF(d + arrow2 - arrow1, 0.0));

    if (isZero(r2))
    {
        path.lineTo(path.currentPosition() - QPointF(0.0, 2 * h));
    }
    else
    {
        // Рисуем 2ю поверхность (сверху вниз)
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

    // Замыкаем контур
    path.closeSubpath();

    return path;
}
