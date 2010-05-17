#include <QtGui>
#include <QDir>
#include <QDebug>

const QString DIR = "./tmpdir";

int main(int argc, char *argv[])
{
	QDir dir;
	
	if (dir.exists(DIR)) {
		qDebug() <<__FILE__ << __LINE__ << __func__ << "dir exist";
		return 0;
	}

	if (dir.mkdir(DIR)) {
		qDebug() <<__FILE__ << __LINE__ << __func__ << "mkdir";
		return 0;
	}
    
	return 0;
}
