#include "input_window.h"

#include "lens.h"
#include "output_window.h"
#include "ray.h"

#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

InputWindow::InputWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    r1_input_line = make_new_input_line("r1");
    r2_input_line = make_new_input_line("r2");
    lens_h_input_line = make_new_input_line("h of lens");
    d_input_line = make_new_input_line("d");
    n_input_line = make_new_input_line("n");

    alpha_input_line = make_new_input_line("alpha");
    ray_h_input_line = make_new_input_line("h of ray");

    layout->addWidget(r1_input_line);
    layout->addWidget(r2_input_line);
    layout->addWidget(lens_h_input_line);
    layout->addWidget(d_input_line);
    layout->addWidget(n_input_line);

    layout->addWidget(alpha_input_line);
    layout->addWidget(lens_h_input_line);

    QPushButton *compute_button = new QPushButton("compute", this);
    layout->addWidget(compute_button);
    connect(compute_button, &QPushButton::clicked, this, &InputWindow::on_compute_clicked);

    QPushButton *fill_button = new QPushButton("fill", this);
    layout->addWidget(fill_button);
    connect(fill_button, &QPushButton::clicked, this, &InputWindow::on_fill_clicked);

    resize(500, 500);
}

void InputWindow::on_compute_clicked()
{
    try
    {
        const double r1 = r1_input_line->text().toDouble();
        const double r2 = r2_input_line->text().toDouble();
        const double lens_h = lens_h_input_line->text().toDouble();
        const double d = d_input_line->text().toDouble();
        const double n = n_input_line->text().toDouble();

        const Lens lens(r1, r2, lens_h, d, n);

        const double alpha = alpha_input_line->text().toDouble();
        const double ray_h = ray_h_input_line->text().toDouble();

        const Ray ray{alpha, ray_h};

        OutputWindow *output_window = new OutputWindow(lens, ray, this);
        output_window->show();
    }
    catch (...)
    {
        // TODO
    }
}

void InputWindow::on_fill_clicked()
{
    r1_input_line->setText("50");
    r2_input_line->setText("-50");
    lens_h_input_line->setText("15");
    d_input_line->setText("5");
    n_input_line->setText("1.5");

    alpha_input_line->setText("45");
    ray_h_input_line->setText("7.5");
}

QLineEdit *InputWindow::make_new_input_line(const QString &placeholder)
{
    QLineEdit *input = new QLineEdit(this);

    input->setPlaceholderText(placeholder);

    QDoubleValidator *validator = new QDoubleValidator(-999.9, 999.9, 8, this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    input->setValidator(validator);

    return input;
}
