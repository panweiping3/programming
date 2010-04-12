#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDebug>

class MyObject : public QObject
{
		Q_OBJECT

		public:
				MyObject(QObject *parent = 0);

		protected:
				void timerEvent(QTimerEvent *event);
};

#endif

