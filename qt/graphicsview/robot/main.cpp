#include "coloritem.h"
#include "robot.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	QGraphicsScene scene(-200, -200, 400, 400);

	for (int i=0; i<10; ++i)
	{
		ColorItem *item = new ColorItem;
		item->setPos(::sin((i * 6.28) / 10.0) * 150, ::cos((i * 6.28) / 10.0) * 150);
		scene.addItem(item);
	}

	Robot *robot = new Robot;
	robot->scale(1.2, 1.2);
	robot->setPos(0, -20);
	scene.addItem(robot);

	QGraphicsView view(&scene);
	view.setRenderHint(QPainter::Antialiasing);
	view.setCacheMode(QGraphicsView::CacheBackground);
	view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view.setBackgroundBrush(QColor(230, 200, 167));
	view.resize(400, 300);
	
	view.show();

	return app.exec();
}
