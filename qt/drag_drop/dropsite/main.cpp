#include "dropsitewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	DropSiteWindow window;
	window.show();

	return app.exec();
}
