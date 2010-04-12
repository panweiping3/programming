#include "stylewindow.h"
#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QStyle *style = QStyleFactory::create("simplestyle");
qDebug() << (int)style;

	QApplication::setStyle(style);

	StyleWindow window;
	window.resize(200, 50);
	window.show();

	return app.exec();
}
