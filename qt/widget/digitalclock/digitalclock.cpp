#include "digitalclock.h"

#include <QtGui>


DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    setNumDigits(8);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime())); 
    timer->start(1000);

    showTime();
    setWindowTitle(tr("Digital Clock"));
    resize(150, 60);
}

void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("h:m:s");
qDebug() << text;
    if ((time.second() % 2) == 0) {
        //text[3] = ' ';
    }
    
    display(text);

    //display("1234567890");
}
