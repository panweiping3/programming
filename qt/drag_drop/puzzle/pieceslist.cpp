#include "pieceslist.h"

PiecesList::PiecesList(QWidget *parent)
	: QListWidget(parent)
{
	setDragEnabled(true);
	setAcceptDrops(true);
	setViewMode(QListView::IconMode);
	setIconSize(QSize(60, 60));
	setSpacing(10);
	setDropIndicatorShown(true);
}

void PiecesList::addPiece(QPixmap pixmap, QPoint location)
{
qDebug() << __FILE__ << "PiecesList::addPiece";
	QListWidgetItem *pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(pixmap));
	pieceItem->setData(Qt::UserRole, QVariant(pixmap));
	pieceItem->setData(Qt::UserRole + 1, location);
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void PiecesList::dragEnterEvent(QDragEnterEvent *event)
{
qDebug() << __FILE__ << "PiecesList::dropEnterEvent";
	if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void PiecesList::dragMoveEvent(QDragMoveEvent *event)
{
qDebug() << __FILE__ << "PiecesList::dropMoveEvent";
	if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void PiecesList::dropEvent(QDropEvent *event)
{
qDebug() << __FILE__ << "PiecesList::dropEvent";
	if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
	{
		QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
		QPixmap pixmap;
		QPoint location;
		dataStream >> pixmap >> location;
		
		addPiece(pixmap, location);
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void PiecesList::startDrag(Qt::DropActions supportedActions)
{
qDebug() << __FILE__ << "PiecesList::startDrag";
	QListWidgetItem *item = currentItem();
	
	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
	QPoint location = item->data(Qt::UserRole + 1).toPoint();

	dataStream << pixmap << location;
	
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("image/x-puzzle-piece", itemData);
	
	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
	drag->setPixmap(pixmap);

	if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
	{
qDebug() << row(item);
		delete takeItem(row(item));
	}
}
