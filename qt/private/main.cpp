#include <QtCore/QCoreApplication>
#include "slotTest.h"

int main(int argc,char* argv[])
{
	QCoreApplication app(argc,argv);   
	slotTest bob;   
	app.exec();
}
