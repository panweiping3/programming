#include <QObject>
#include <QDebug>

#include "counter.h"

Counter::Counter() 
{ 
	m_value = 0; 
}
     	
void Counter::setValue(int value) 
{ 
	m_value = value; 
	qDebug() << "Counter send a signal, value is:" << m_value;
	emit valueChanged(m_value); 
}
