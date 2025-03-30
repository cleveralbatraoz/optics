#include "input_window.h"

#include "lens.h"
#include "output_window.h"

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
    d_input_line = make_new_input_line("d");
    h_input_line = make_new_input_line("h");
    n_input_line = make_new_input_line("n");

    layout->addWidget(r1_input_line);
    layout->addWidget(r2_input_line);
    layout->addWidget(d_input_line);
    layout->addWidget(h_input_line);
    layout->addWidget(n_input_line);

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
        const double d = d_input_line->text().toDouble();
        const double h = h_input_line->text().toDouble();
        const double n = n_input_line->text().toDouble();

        const Lens lens(r1, r2, d, h, n);

        OutputWindow *output_window = new OutputWindow(lens, this);
        output_window->show();
    }
    catch (...)
    {
        // TODO
    }
}

void InputWindow::on_fill_clicked()
{
    r1_input_line->setText("-500");
    r2_input_line->setText("500");
    d_input_line->setText("50");
    h_input_line->setText("-10");
    n_input_line->setText("1.5");
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
