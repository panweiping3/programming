#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QObject>
#include <QBrush>

class Car :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    public:
        Car();
        QRectF boundingRect() const;

    public slots:
        void accelerate();
        void decelerate();
        void turnLeft();
        void turnRight();
    signals:
        void crashed();
    protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        void timerEvent(QTimerEvent *event);
    private:
        QBrush color;
        qreal wheelsAngle;
        qreal speed;
};

#endif
