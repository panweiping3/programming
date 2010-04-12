#include <QApplication>
#include <QDialog>
#include "newDialog.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	NewDialog *dialog = new NewDialog;
	dialog->show();
	
	return app.exec();
}
