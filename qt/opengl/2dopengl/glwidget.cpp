#include <QtGui> 
#include "helper.h"
#include "glwidget.h"

GLWidget::GLWidget(Helper *helper, QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
{
	elapsed = 0;
	setFixedSize(200, 200);	
}

void GLWidget::animate()
{
	elapsed = (elapsed + qobject_cast<QTimer *>(sender())->interval()) % 1000;
	repaint();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	helper->paint(&painter, event, elapsed);
	painter.end();
}


