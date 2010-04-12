#ifndef ITEM_H 
#define ITEM_H

#include <QtGui>

class Item : public QGraphicsItem
{
	public:
		Item();

		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
							QWidget *widget);
};

#endif
