#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(puzzle);

    QApplication app(argc, argv);

    MainWindow window;
    window.openImage(":/images/example.jpg");
    window.show();

    return app.exec();
}
