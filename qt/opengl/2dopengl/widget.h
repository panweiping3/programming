#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Helper;
class QPaintEvent;

class Widget : public QWidget
{
	Q_OBJECT

	public:
		Widget(Helper *helper, QWidget *parent);
		
	public slots:
		void animate();

	protected:
		void paintEvent(QPaintEvent *event);
	
	private:
		Helper *helper;
		int elapsed;
};

#endif
