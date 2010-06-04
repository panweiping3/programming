#include <QtGui>
#include <QDir>
#include <QFile>
#include <QDebug>

const QString TMPFILE = "pwp";
const QString TMPDIR = "./tmpdir/";

int main(int argc, char *argv[])
{
	QFile file(TMPFILE);
	
	if (file.open(QIODevice::WriteOnly)) {
		qDebug() <<__FILE__ << __LINE__ << __func__ << "create file ok";
	} else {
		qDebug() <<__FILE__ << __LINE__ << __func__ << "create file error";
		return -1;
	}

	QString str = TMPFILE + TMPDIR;

	file.write(str.toUtf8().data(), str.size());
	file.close();
	return 0;
}
