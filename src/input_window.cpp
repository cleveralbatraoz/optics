#include "input_window.h"

#include "lens.h"
#include "output_window.h"
#include "ray.h"

#include <QDoubleValidator>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <algorithm>
#include <cmath>

InputWindow::InputWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Define the width based on the label with the maximum length
    const int labelWidth = 80; // Example fixed width, adjust as needed

    // Create a group box to hold the inputs
    QGroupBox *inputsGroupBox = new QGroupBox("Lens Parameters");

    // Create a layout for the group box
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(inputsGroupBox);

    // Add labeled input lines to the group box
    groupBoxLayout->addWidget(make_labeled_input_line("r1:", r1_input_line, labelWidth));
    groupBoxLayout->addWidget(make_labeled_input_line("r2:", r2_input_line, labelWidth));
    groupBoxLayout->addWidget(make_labeled_input_line("h of lens:", lens_h_input_line, labelWidth));
    groupBoxLayout->addWidget(make_labeled_input_line("d:", d_input_line, labelWidth));
    groupBoxLayout->addWidget(make_labeled_input_line("n:", n_input_line, labelWidth));
    groupBoxLayout->addWidget(make_labeled_input_line("α of ray:", alpha_input_line, labelWidth));
    groupBoxLayout->addWidget(make_labeled_input_line("h of ray:", ray_h_input_line, labelWidth));

    // Add the group box to the main layout
    mainLayout->addWidget(inputsGroupBox);

    // Add control buttons
    QPushButton *computeButton = new QPushButton("Compute", this);
    mainLayout->addWidget(computeButton);
    connect(computeButton, &QPushButton::clicked, this, &InputWindow::on_compute_clicked);

    // Set a fixed size for the window
    resize(500, 500);
}

void InputWindow::on_compute_clicked()
{
    bool ok = true;

    const double r1 = r1_input_line->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect r1");
        return;
    }

    const double r2 = r2_input_line->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect r2");
        return;
    }

    const double lens_h = lens_h_input_line->text().toDouble(&ok);
    if (!ok || lens_h <= 0.0 || lens_h > std::min(fabs(r1), fabs(r2)))
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect lens_h");
        return;
    }

    const double d = d_input_line->text().toDouble(&ok);
    if (d <= 0.0)
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect d");
        return;
    }

    const double n = n_input_line->text().toDouble(&ok);
    if (n <= 1.0)
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect n");
        return;
    }

    const double alpha = alpha_input_line->text().toDouble(&ok);
    if (fabs(alpha) > 90.0)
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect alpha");
        return;
    }

    const double ray_h = ray_h_input_line->text().toDouble(&ok);
    if (fabs(ray_h) > lens_h)
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Incorrect input", "Incorrect ray_h");
        return;
    }

    const Lens lens(r1, r2, lens_h, d, n);
    const Ray ray{alpha, ray_h};

    OutputWindow *output_window = new OutputWindow(lens, ray, this);
    output_window->show();
}

QWidget *InputWindow::make_labeled_input_line(const QString &labelText, QLineEdit *&lineEdit, int labelWidth)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);

    QLabel *label = new QLabel(labelText);
    label->setFixedWidth(labelWidth);                       // Align labels by setting a fixed width
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter); // Align text to the right
    lineEdit = new QLineEdit;
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    return widget;
}
