#include <QCoreApplication>
#include <QTest>

#include "counter.h" 
#include "counterdisplay.h" 

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    
    Counter counter;
	CounterDisplay display;
    QObject::connect(&counter, SIGNAL(valueChanged(int)), &display, SLOT(showValue(int)));

	for (int i=0; i<100; ++i) {
		counter.setValue(i);
		QTest::qSleep(1000);
	}
    
	return app.exec();
}
