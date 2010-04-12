#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QFrame>

class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QFrame
{
	public:
		DragWidget(QWidget *parent=0);

	protected:
		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		void dropEvent(QDropEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
};

#endif
