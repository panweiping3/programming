#ifndef ROBOT_H 
#define ROBOT_H

#include <QGraphicsItem>

class QGraphicsSceneMouseEvent;
class QTimeLine;

class RobotPart : public QGraphicsItem
{
	public:
		RobotPart(QGraphicsItem *parent = 0);

	protected:
		void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
		void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
		void dropEvent(QGraphicsSceneDragDropEvent *event);

		QPixmap pixmap;
		QColor color;
		bool dragOver;
};

class RobotHead : public RobotPart
{
	public:
		RobotHead(QGraphicsItem *parent = 0);

		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		enum 
		{
			Type = UserType + 1
		};

		int type() const;
};

class RobotTorso : public RobotPart
{
	public:
		RobotTorso(QGraphicsItem *parent = 0);

		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class RobotLimb : public RobotPart
{
	public:
		RobotLimb(QGraphicsItem *parent = 0);

		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class Robot : public RobotPart
{
	public:
		Robot();
		~Robot();

		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		
	private:
		QTimeLine *timeLine;
};
#endif
