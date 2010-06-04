#include <QtGlobal>
#include <QDebug>

int main(int argc, char *argv[])
{
	qint32 i = 0;
	for (;;) {
		i++;
		qDebug() <<__FILE__ << __LINE__ << __func__ << i;	
	}

	return 0;
}
