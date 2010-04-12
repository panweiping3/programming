#include <QtCore/QObject>
#include <QTimer>
#include "slotTest.h"
#include "slotTest_p.h"
#include "moc_slotTest.cpp"

slotTest::slotTest() : QObject()
{
	d_ptr = new slotTestPrivate(this);   
	timer = new QTimer(this);   
	timer->setInterval(1000);   
	connect(timer,SIGNAL(timeout()),this,SLOT(bob()));   
	timer->start();
	Q_D(slotTest);
	d->slotPrivate();
	d_func()->slotPrivate();
	d_ptr->slotPrivate();
}
