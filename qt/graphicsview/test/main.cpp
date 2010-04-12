#include "item.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QGraphicsScene scene;
	scene.setSceneRect(-300, -300, 600, 600);
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);

	Item *item = new Item;
	scene.addItem(item);

	QGraphicsView view(&scene);
	view.setRenderHint(QPainter::Antialiasing);
	view.setCacheMode(QGraphicsView::CacheBackground);
	view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view.setDragMode(QGraphicsView::ScrollHandDrag);
	view.resize(400, 300);
	
	view.show();

	return app.exec();
}
