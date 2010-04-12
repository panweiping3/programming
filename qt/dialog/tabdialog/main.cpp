#include "tabdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(tabdialog);

	QApplication app(argc, argv);
	
	QString fileName;	

	if (argc >= 2)
	{
		fileName = argv[1];
	}
	else
	{
		fileName = ".";
	}

	TabDialog tabdialog(fileName);
	tabdialog.show();

	return app.exec();
}
