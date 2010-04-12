#include "draglabel.h"

#include <QtGui>

DragLabel::DragLabel(const QString &text, QWidget *parent)
	: QLabel(text, parent)
{
	setAutoFillBackground(true);
	setFrameShape(QFrame::Panel);
	setFrameShadow(QFrame::Raised);
}
	
void DragLabel::mousePressEvent(QMouseEvent *event)
{
	QPoint hotSpot = event->pos();
	
	QMimeData *mimeData = new QMimeData;
	mimeData->setText(text());
	mimeData->setData("application/x-hotspot", QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

	// craete this pixmap in order to show it when drag	
	QPixmap pixmap(size());
	render(&pixmap);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(pixmap);
	drag->setHotSpot(hotSpot);		

	Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
	
	if (dropAction == Qt::MoveAction)
	{
		close();
		update();
	}
}
