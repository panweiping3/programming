#include <QtGui>
#include <QDir>
#include <QFile>
#include <QDebug>

const QString TMPFILE = "./tmpdir/pwp";
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

	qDebug() <<__FILE__ << __LINE__ << __func__ << file.size();
	//NOTE
	//if use WriteOnly, all data that overlap by seek is set '\0'
	file.seek(4);
	file.write("444");
	qDebug() <<__FILE__ << __LINE__ << __func__ << file.pos();
	file.close();
	return 0;
}
