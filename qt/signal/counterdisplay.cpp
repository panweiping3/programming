#include <QDebug>

#include "counterdisplay.h"

CounterDisplay::CounterDisplay()
{
	;	
}

void CounterDisplay::showValue(int value) 
{ 
	qDebug() << "CounterDisplay reveive a signal, value is:" << value;
	qDebug() << "value is:" << value;
}
