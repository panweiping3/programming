#include <QtGui>

#ifndef QT_NO_CONCURRENT
using namespace QtConcurrent;

const int iterations = 20;

void spin(int &iteration)
{
	const int work = 1000 * 1000 * 400;
	volatile int v = 0;

	for (int j=0; j<work; ++j)
		++v;
	
	qDebug() << "iteration" << iteration << "in thread"<< QThread::currentThread();
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	QVector<int> vector;
	
	for (int i=0; i<iterations; ++i)
		vector.append(i);

	QProgressDialog dialog;
	dialog.setLabelText(QString("Progressing using %1 thraed(s)...").arg(QThread::idealThreadCount()));

	QFutureWatcher<void> futureWatcher;
	QObject::connect(&futureWatcher, SIGNAL(finished()), &dialog, SLOT(reset()));
	QObject::connect(&dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
	QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int, int)), &dialog, SLOT(setRange(int, int)));
	QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), &dialog, SLOT(setValue(int)));

	futureWatcher.setFuture(QtConcurrent::map(vector, spin));

	dialog.exec();
	futureWatcher.waitForFinished();
	qDebug() << "Canceled ?" << futureWatcher.future().isCanceled();
}

#else

int main()
{
	 qDebug() << "Qt Concurrent is not yet supported on this platform";
}

#endif
