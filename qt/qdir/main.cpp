#include <QtGui>
#include <QDir>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
	QDir dir("/tmp/big_file/");
	
	QFileInfoList list = 
	dir.entryInfoList(QStringList("rfbackup_bigfile_data_*"), 
								QDir::Files|QDir::Writable, 
								QDir::Name);
	for (int i=0; i<list.size(); ++i) {
		qDebug() <<__FILE__ << __LINE__ << __func__ << list.at(i).absoluteFilePath();
	}
	qDebug() <<__FILE__ << __LINE__ << __func__ << list.size();
	//qDebug() <<__FILE__ << __LINE__ << __func__ << list;
	return 0;
}
