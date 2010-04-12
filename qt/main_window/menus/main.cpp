#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(menus);
	
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	
	return app.exec();
}
