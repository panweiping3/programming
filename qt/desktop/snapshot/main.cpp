#include "screenshot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	Screenshot screenshot;
	screenshot.show();
	
	return app.exec();
}
