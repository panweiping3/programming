#include <QApplication>

#include "configdialog.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(configdialog);
	
	QApplication app(argc, argv);
	ConfigDialog dialog;
	
	return dialog.exec();
}
