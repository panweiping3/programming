#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class Helper;
class QPaintEvent;
class QWidget;

class GLWidget : public QGLWidget
{
	Q_OBJECT

	public:
		GLWidget(Helper *helper, QWidget *parent);
		
	public slots:
		void animate();

	protected:
		void paintEvent(QPaintEvent *event);
	
	private:
		Helper *helper;
		int elapsed;
};

#endif
