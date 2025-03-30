#pragma once

#include "lens.h"
#include "ray.h"

#include <QDialog>

class OutputWindow : public QDialog
{
    Q_OBJECT

  public:
    OutputWindow(const Lens &lens, const Ray &ray, QWidget *parent = nullptr);
};
