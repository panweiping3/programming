#include <QApplication>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QString desktopPath;
	desktopPath = QDir::homePath() + QString("/Desktop");
	QDir desktopDir(desktopPath);

	if (!desktopDir.exists())
	{
		mkdir(QFile::encodeName(desktopPath), S_IRWXU);
		qDebug() << "I make a dir ";
	}
	return app.exec();
}
