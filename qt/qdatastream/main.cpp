#include <QtGui>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QFile file("./tmp");
    file.open(QIODevice::WriteOnly);
    QDataStream data(&file);

    file.close();

	return 0; 
}
