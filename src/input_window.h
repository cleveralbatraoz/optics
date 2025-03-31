#pragma once

#include <QLineEdit>
#include <QString>
#include <QWidget>

class InputWindow : public QWidget
{
    Q_OBJECT

  public:
    InputWindow(QWidget *parent = nullptr);

  private slots:
    void on_compute_clicked();

  private:
    QWidget *make_labeled_input_line(const QString &labelText, QLineEdit *&lineEdit, int labelWidth);

    QLineEdit *r1_input_line = nullptr;
    QLineEdit *r2_input_line = nullptr;
    QLineEdit *lens_h_input_line = nullptr;
    QLineEdit *d_input_line = nullptr;
    QLineEdit *n_input_line = nullptr;

    QLineEdit *alpha_input_line = nullptr;
    QLineEdit *ray_h_input_line = nullptr;
};
