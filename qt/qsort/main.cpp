#include <QApplication>
#include <QDebug>
#include <QtAlgorithms>
#include <QStringList>

bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
	return s1.toLower() < s2.toLower();
}

int doSomething()
{
	QStringList list;
	list << "AlPha" << "beTA" << "gamma" << "DELTA";
	qDebug() <<__FILE__ << __LINE__ << __func__ << list;
	qStableSort(list.begin(), list.end(), caseInsensitiveLessThan);
	qDebug() <<__FILE__ << __LINE__ << __func__ << list;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	doSomething();
	return app.exec();
} 
