#include "input_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    InputWindow input_window;
    input_window.show();

    return app.exec();
}
