#pragma once

#include "lens.h"
#include "ray.h"

#include <QPainter>
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
    QPainterPath composePainterPath();

    Lens lens;
    Ray ray;
};
