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

    // Вычисляем стрелку прогиба поверхностей

    double dArrow1 = 0.0;
    double dArrow2 = 0.0;

    if (!isZero(r1))
    {
        dArrow1 = fabs(r1) - sqrt(r1 * r1 - h1 * h1);
    }
    if (r1 < 0.0)
    {
        dArrow1 = -dArrow1;
    }

    if (!isZero(r2))
    {
        dArrow2 = fabs(r2) - sqrt(r2 * r2 - h2 * h2);
    }
    if (r2 < 0.0)
    {
        dArrow2 = -dArrow2;
    }

    // Первая точка контура - верхняя точка поверхности
    path.moveTo(dArrow1, -h);

    if (isZero(r1))
    {
        path.lineTo(path.currentPosition() + QPointF(0.0, 2 * h));
    }
    else
    {
        // Рисуем 1ю поверхность (сверху вниз)
        double dAngle = asin(h1 / r1) * 180 / std::numbers::pi; // угол между осью и крайней точкой поверхности
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
    path.lineTo(path.currentPosition() + QPointF(d + dArrow2, 0.0));

    if (isZero(r2))
    {
        path.lineTo(path.currentPosition() - QPointF(0.0, 2 * h));
    }
    else
    {
        // Рисуем 2ю поверхность (сверху вниз)
        double dAngle = asin(h2 / r2) * 180 / std::numbers::pi;
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
