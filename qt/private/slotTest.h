#ifndef SLOTTEST_H_
#define SLOTTEST_H_
#include <QtCore/QObject>
class slotTestPrivate;
class QTimer;

class slotTest : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(slotTest)
	public:
		slotTest();
		void slotPublic(){ qWarning("slot public!"); }
	private:
		Q_PRIVATE_SLOT(d_func(),void bob())
		QTimer * timer;   
		slotTestPrivate * d_ptr;
};
#endif
