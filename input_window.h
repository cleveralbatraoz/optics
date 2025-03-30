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
    void on_fill_clicked();

  private:
    QLineEdit *make_new_input_line(const QString &placeholder);

    QLineEdit *r1_input_line = nullptr;
    QLineEdit *r2_input_line = nullptr;
    QLineEdit *d_input_line = nullptr;
    QLineEdit *h_input_line = nullptr;
    QLineEdit *n_input_line = nullptr;
    // QLineEdit *ray_height_input_line = nullptr;
    QLineEdit *ray_angle_input_line = nullptr;
};
