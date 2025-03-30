#include "lens_painter.h"

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

LensPainter::LensPainter(const Lens &lens, QWidget *parent) : QWidget(parent), lens(lens)
{
    setFixedSize(600, 600);
}

void LensPainter::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2));

    QPainterPath path = composePainterPath();

    QRectF pathRect = path.boundingRect();
    QRect widgetRect = rect();
    qreal scaleX = widgetRect.width() / pathRect.width();
    qreal scaleY = widgetRect.height() / pathRect.height();
    qreal scale = std::min(scaleX, scaleY) / 2;
    QPointF widgetCenter = widgetRect.center();
    painter.translate(widgetCenter);
    painter.scale(scale, scale);

    // painter.setBrush(Qt::blue);
    painter.fillPath(path, Qt::blue);

    // painter.setPen(QPen(Qt::black, 1, Qt::DashDotLine));
    // painter.drawLine(0, centerY, width, centerY);
}

QPainterPath LensPainter::composePainterPath()
{
    QPainterPath path;

    double h1 = lens.get_h();
    double h2 = lens.get_h();

    double r1 = lens.get_r1();
    double r2 = lens.get_r2();
    double h = lens.get_h();
    double d = lens.get_d();

    double dX_p = 0;
    double dY_p = 0;

    // Вычисляем стрелку прогиба поверхностей
    double dArrow1 = fabs(r1) - sqrt(r1 * r1 - h1 * h1);
    if (r1 < 0)
        dArrow1 = -dArrow1;

    double dArrow2 = fabs(r2) - sqrt(r2 * r2 - h2 * h2);
    if (r2 < 0)
        dArrow2 = -dArrow2;

    // Первая точка контура - верхняя точка поверхности
    path.moveTo(dX_p + dArrow1, dY_p - h);

    // Рисуем 1ю поверхность (сверху вниз)
    double dAngle = asin(h1 / r1) * 180 / std::numbers::pi; // угол между осью и крайней точкой поверхности
    if (r1 > 0)
        path.arcTo(dX_p, dY_p - r1, r1 * 2, r1 * 2, 180 - dAngle, dAngle * 2);
    else
        path.arcTo(dX_p + 2 * r1, dY_p + r1, -r1 * 2, -r1 * 2, -dAngle, dAngle * 2);

    // Добавляем нижнюю линию между поверхностями
    path.lineTo(dX_p + d + dArrow2, dY_p + h);
    dX_p += d;

    // Рисуем 2ю поверхность (сверху вниз)
    dAngle = asin(h2 / r2) * 180 / std::numbers::pi;
    if (r2 > 0)
        path.arcTo(dX_p, dY_p - r2, r2 * 2, r2 * 2, 180 + dAngle, -dAngle * 2);
    else
        path.arcTo(dX_p + 2 * r2, dY_p + r2, -r2 * 2, -r2 * 2, dAngle, -dAngle * 2);

    // Замыкаем контур
    path.closeSubpath();

    return path;
}
