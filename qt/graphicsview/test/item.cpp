#include "item.h"

Item::Item()
{}

QRectF Item::boundingRect() const
{
	qreal adjust = 0.5;
	return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
							QWidget *widget)
{
	painter->setBrush(Qt::blue);
	painter->drawEllipse(-10, -20, 20, 40);

	painter->setBrush(Qt::white);
	painter->drawEllipse(-10, -17, 8, 8);
	painter->drawEllipse(2, -17, 8, 8);

	painter->setBrush(Qt::black);
	painter->drawEllipse(QRectF(-2, -22, 4, 4));

	painter->drawEllipse(QRectF(-8.0 , -17, 4, 4));
	painter->drawEllipse(QRectF(4.0 , -17, 4, 4));

	painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);	
	painter->drawEllipse(-17, -12, 16, 16);
	painter->drawEllipse(1, -12, 16, 16);

	QPainterPath path(QPointF(0, 20));
	path.cubicTo(-5, 22, -5, 22, 0, 25);
	path.cubicTo(5, 27, 5, 32, 0, 30);
	path.cubicTo(-5, 32, -5, 42, 0, 35);
	painter->setBrush(Qt::NoBrush);
	painter->drawPath(path);

	painter->setBrush(Qt::red);
	painter->drawEllipse(10, 0, 20, 40);

	painter->setBrush(Qt::white);
	painter->drawEllipse(10, 3, 8, 8);
	painter->drawEllipse(22, 3, 8, 8);

	painter->setBrush(Qt::black);
	painter->drawEllipse(QRectF(18, -2, 4, 4));

	painter->drawEllipse(QRectF(12 , 3, 4, 4));
	painter->drawEllipse(QRectF(24 , 3, 4, 4));

	painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);	
	painter->drawEllipse(3,  8, 16, 16);
	painter->drawEllipse(21, 8, 16, 16);

	path.moveTo(QPointF(20, 40));
	path.cubicTo(15, 42, 15, 42, 20, 45);
	path.cubicTo(25, 47, 25, 52, 20, 50);
	path.cubicTo(15, 52, 15, 62, 20, 55);
	painter->setBrush(Qt::NoBrush);
	painter->drawPath(path);
};
