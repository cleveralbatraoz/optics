#pragma once

#include "lens.h"

#include <QPainter>
#include <QPainterPath>
#include <QWidget>

class LensPainter : public QWidget
{
    Q_OBJECT

  public:
    LensPainter(const Lens &lens, QWidget *parent = nullptr);

  protected:
    virtual void paintEvent(QPaintEvent *event) override;

  private:
    QPainterPath composePainterPath();

    Lens lens;
};
