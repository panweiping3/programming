#include <QtGui>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    
    QFile file("./tmp");

    file.open(QIODevice::WriteOnly);

    QString str("pwp is good\n");
    QDataStream data(&file);
    data << str;
    file.close();
   
    file.open(QIODevice::ReadOnly);
    QDataStream read_data(&file);
    read_data >> str;
    qDebug() <<__FILE__ << __LINE__ << __func__ << read_data;
    qDebug() <<__FILE__ << __LINE__ << __func__ << str;
    file.close();

	//return app.exec();
	return 0; 
}
