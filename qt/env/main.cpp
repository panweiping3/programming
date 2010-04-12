#include <QCoreApplication>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	QByteArray env = qgetenv("HOME");	
	qDebug() << "home:" << env;
    	
	env = qgetenv("PWP");	
	qDebug() << "PWP:" << env;
//	return app.exec();
}
