#include "dragwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(draggabletext);

	QApplication app(argc, argv);
	
	DragWidget window;
	window.show();

	return app.exec();
}
