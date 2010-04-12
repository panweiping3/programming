#include <QApplication>
#include <QtGui>
#include "addressbook.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	AddressBook *addressBook = new AddressBook;
	addressBook->show();	

	return app.exec();
}
