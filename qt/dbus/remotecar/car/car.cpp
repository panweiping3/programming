#include "car.h"
#include <QtGui/QtGui>
#include <math.h>

static const double Pi = 3.1415926;

Car::Car() : color(Qt::green), wheelsAngle(0), speed(0)
{
    startTimer(1000/33);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

QRectF Car::boundingRect() const
{
    return QRectF(-35, -81, 70, 115);
}

void Car::accelerate()
{
    if (speed < 10) {
        ++speed;
    }
}
void Car::decelerate()
{
    if (speed > - 10) {
        --speed;
    }
}

void Car::turnLeft()
{
    if (wheelsAngle > -30) {
        wheelsAngle -= 5;
    }
}

void Car::turnRight()
{
    if (wheelsAngle < 30) {
        wheelsAngle +=5;
    }
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::gray);
    painter->drawRect(-20, -58, 40, 2);
    painter->drawRect(-20, 7, 40, 2);

    painter->setBrush(color);
    painter->drawRect(-25, -79, 50, 10);

    painter->drawEllipse(-25, -48, 50, 20);
    painter->drawRect(-25, -38, 50, 35);
    painter->drawRect(-5, 9, 10, 10);

    painter->drawEllipse(-10, -81, 20, 100);
    painter->drawRect(-17, 19, 34, 15);

    painter->setBrush(Qt::black);
    painter->drawPie(-5, -51, 10, 15, 0, 180 * 16);
    painter->drawRect(-5, -44, 10, 10);

    painter->save();
    painter->translate(-20, -58);
    painter->rotate(wheelsAngle);
    painter->drawRect(-10, -7, 10, 15);
    painter->restore();

    painter->save();
    painter->translate(20, 58);
    painter->rotate(wheelsAngle);
    painter->drawRect(0, -7, 10, 15);
    painter->restore();

    painter->drawRect(-30, 0, 12, 17);
    painter->drawRect(19, 0, 12, 17);
}

void Car::timerEvent(QTimerEvent *event)
{
    const qreal axelDistance = 54;
    qreal wheelsAngleRads = (wheelsAngle * Pi) / 180;
    qreal turnDistance = ::cos(wheelsAngleRads) * axelDistance * 2;
    qreal turnRateRads = wheelsAngleRads / turnDistance;
    qreal turnRate = (turnRateRads * 180) / Pi;
    qreal rotation = speed * turnRate;

    rotate(rotation);
    translate(0, -speed);
    update();
}
