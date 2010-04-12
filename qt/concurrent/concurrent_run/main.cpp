#include <QDebug> 
#include <QThread> 
#include <QString> 
#include <qtconcurrentrun.h>

#ifndef QT_NO_CONCURRENT

using namespace QtConcurrent;

QThread *hello(QString name)
{
	qDebug() << "Hello" << name << "from" << QThread::currentThread();
	return QThread::currentThread();
} 

int main()
{
	QFuture<QThread *> f1 = run(hello, QString("Alice"));
	QFuture<QThread *> f2 = run(hello, QString("Bob"));
	f1.waitForFinished();
	f2.waitForFinished();

	qDebug() << f1.isFinished() << f1.resultCount() << f1.result(); 
	qDebug() << f2.isFinished() << f2.resultCount() << f2.result(); 
}

#else
int main()
{
	qDebug() << "Qt Concurrent is not yet supported";
}
#endif
