#include "digitalclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DigitalClock clock;
    clock.show();
    return app.exec();
}
