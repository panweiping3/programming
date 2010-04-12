#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include "finddialog.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QPixmap pixmap("./images/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();

	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	splash->showMessage(QObject::tr("starting main window"), topRight, Qt::white);

	FindDialog *dialog = new FindDialog;

	splash->showMessage(QObject::tr("loading window"), topRight, Qt::white);
	dialog->show();

	splash->finish(dialog);
	delete splash;

	return app.exec();
}
