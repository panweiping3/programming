#include <QCoreApplication>
#include <QTime> 
#include <QDebug> 

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QTime time;
	qDebug() <<__FILE__ << __LINE__ << __func__ << time.currentTime().toString(); 
	time.start();
	for (int i=0; i < 100; ++i) {
		for (int j=0; j<100; ++j)
		{
			int m = i*8+j;
			if (j % 10) 
			{
				qDebug() <<__FILE__ << __LINE__ << __func__;	
			}
		}
	}
	qDebug() <<__FILE__ << __LINE__ << __func__ << time.currentTime().toString(); 
	qDebug() <<__FILE__ << __LINE__ << __func__ << time.elapsed();	
 //  	return app.exec();
}

