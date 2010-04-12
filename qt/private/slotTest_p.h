#ifndef SLOTTEST_P_H_
#define SLOTTEST_P_H_
#include "slotTest.h"

class slotTestPrivate
{
	Q_DECLARE_PUBLIC(slotTest)

    public:
        slotTestPrivate(slotTest * qq) : q_ptr(qq) {}
		void slotPrivate(){ qWarning("slot private!"); }

    private:
        void bob() 
		{ 
			Q_Q(slotTest);
			qWarning("bob!"); 
			q->slotPublic();
		}   
        slotTest * q_ptr;
};

#endif
