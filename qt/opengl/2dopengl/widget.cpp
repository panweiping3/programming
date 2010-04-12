#include <QtGui> 
#include "helper.h"
#include "widget.h"

Widget::Widget(Helper *helper, QWidget *parent): QWidget(parent), helper(helper)
{
	elapsed = 0;
	setFixedSize(200, 200);	
}

void Widget::animate()
{
	elapsed = (elapsed + qobject_cast<QTimer *>(sender())->interval()) % 1000;
	repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	helper->paint(&painter, event, elapsed);
	painter.end();
}


