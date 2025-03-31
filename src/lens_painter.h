#pragma once

#include "lens.h"
#include "ray.h"

#include <QLineF>
#include <QPaintEvent>
#include <QPainterPath>
#include <QWidget>

class LensPainter : public QWidget
{
    Q_OBJECT

  public:
    LensPainter(const Lens &lens, const Ray &ray, QWidget *parent = nullptr);

  protected:
    virtual void paintEvent(QPaintEvent *event) override;

  private:
    QPainterPath compose_lens_path();

    static void draw_lens(QPainter &painter, const QPainterPath &lens_path);
    static void draw_lines(QPainter &painter, const QLineF &line1, const QLineF &line2, const QLineF &line3);
    static QPen obtain_default_pen();

    Lens lens;
    Ray ray;
};
