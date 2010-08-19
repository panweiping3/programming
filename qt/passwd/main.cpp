#include <QtGui>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
	QStringList list;
    QFile filePasswd("/etc/passwd");
    filePasswd.open( QIODevice::ReadOnly | QIODevice::Text );
    QTextStream inPasswd( &filePasswd );
    while( !inPasswd.atEnd() ) {
		QString line = inPasswd.readLine();
		QString name = line;
		int pos = name.indexOf(':');
		if (pos >= 0) {
			name.truncate(pos);

			int left = line.indexOf(':', pos + 1);
			int right = line.indexOf(':', left + 1);
			QString number = line.mid(left+1, right - left - 1);
			long n = number.toLong(0);
			if (n < 500 || n > 60000) {
				list << name;
			}
		}
    }
    filePasswd.close();
	
	return 0;
}
