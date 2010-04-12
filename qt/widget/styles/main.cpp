#include "widgetgallery.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(styles);

    QApplication app(argc, argv);
    WidgetGally gallery;
    gallery.show();

    return app.exec();
}
