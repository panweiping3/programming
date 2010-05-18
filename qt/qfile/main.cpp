#include <QtGui>
#include <QDir>
#include <QFile>
#include <QDebug>

const QString TMPFILE = "./tmpdir/pwp";
const QString TMPDIR = "./tmpdir/";

int main(int argc, char *argv[])
{
	QFile file(TMPFILE);
	
	if (file.exists()) {
		qDebug() <<__FILE__ << __LINE__ << __func__ << "file exist";
		return 0;
	} else {
		QDir dir;
		if (!dir.exists(TMPDIR)) {
			if (!dir.mkdir(TMPDIR)) {
				qDebug() <<__FILE__ << __LINE__ << __func__ << "mkdir error";
				return 1;
			}
		}

		if (file.open(QIODevice::ReadWrite)) {
			qDebug() <<__FILE__ << __LINE__ << __func__ << "create file ok";
		} else {
			qDebug() <<__FILE__ << __LINE__ << __func__ << "create file error";
			return -1;
		}

		qDebug() <<__FILE__ << __LINE__ << __func__ << file.size();
		file.write("333");
		qDebug() <<__FILE__ << __LINE__ << __func__ << file.size();
		file.seek(0);
		qDebug() <<__FILE__ << __LINE__ << __func__ << file.pos();
		file.seek(3);
		qDebug() <<__FILE__ << __LINE__ << __func__ << file.pos();
			file.close();
    }
	return 0;
}
