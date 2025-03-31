#include "output_window.h"

#include "lens.h"
#include "lens_painter.h"
#include "paraxial_characteristics.h"
#include "ray.h"

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>

OutputWindow::OutputWindow(const Lens &lens, const Ray &ray, QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    ParaxialCharacteristics paraxial_characteristics = lens.compute_paraxial_characteristics();

    layout->addWidget(new QLabel("F: " + QString::number(paraxial_characteristics.f.front)));
    layout->addWidget(new QLabel("F': " + QString::number(paraxial_characteristics.f.back)));
    layout->addWidget(new QLabel("SF: " + QString::number(paraxial_characteristics.sf.front)));
    layout->addWidget(new QLabel("SF': " + QString::number(paraxial_characteristics.sf.back)));
    layout->addWidget(new QLabel("SH: " + QString::number(paraxial_characteristics.sh.front)));
    layout->addWidget(new QLabel("SH': " + QString::number(paraxial_characteristics.sh.back)));

    LensPainter *lens_painter = new LensPainter(lens, ray, this);
    layout->addWidget(lens_painter);
}
