#include "analogclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	AnalogClock clock;
	clock.show();

	return app.exec();
}
