#include <QTimerEvent>

#include "timer.h"

MyObject::MyObject(QObject *parent)
: QObject(parent)
{
		startTimer(1000);   // 1-second timer
		startTimer(10000);  // 1-minute timer
}

void MyObject::timerEvent(QTimerEvent *event)
{
		qDebug() << "Timer ID:" << event->timerId();

		if (event->timerId() == 1)
			qDebug() << "pwp is good " << event->type();
		else
			qDebug() << "pwp is bad  " << event->type();
}

//##include "timer.moc"
