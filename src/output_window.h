#pragma once

#include "lens.h"

#include <QDialog>

class OutputWindow : public QDialog
{
    Q_OBJECT

  public:
    OutputWindow(const Lens &lens, QWidget *parent = nullptr);
};
