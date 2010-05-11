#include <QtGui>
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    
    QUrl url = QUrl::fromLocalFile(QString("/tmp/Makefile"));
//    QUrl url("http://127.0.0.1/tmp/Makefile");
    qDebug() <<__FILE__ << __LINE__ << __func__ << "host" << url.host();    
    qDebug() <<__FILE__ << __LINE__ << __func__ << "path" << url.path();    
    qDebug() <<__FILE__ << __LINE__ << __func__ << "port" << url.port();    
    qDebug() <<__FILE__ << __LINE__ << __func__ << "toLocalFile" << url.toLocalFile();    
    qDebug() <<__FILE__ << __LINE__ << __func__ << "toString" << url.toString();    
    
	return app.exec();
}
