#include "puzzlewidget.h"

PuzzleWidget::PuzzleWidget(QWidget *parent)
	: QWidget(parent)
{
	setAcceptDrops(true);
	setMinimumSize(IMAGE_SIZE, IMAGE_SIZE);
	setMaximumSize(IMAGE_SIZE, IMAGE_SIZE);
}

void PuzzleWidget::clear()
{
	pieceLocations.clear();
	piecePixmaps.clear();
	pieceRects.clear();
	
	highlightedRect = QRect();
	inPlace = 0;
	update();
}

void PuzzleWidget::dragEnterEvent(QDragEnterEvent *event)
{
qDebug() << __FILE__ << "PuzzleWidget::dragEnterEvent";
	if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void PuzzleWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
qDebug() << __FILE__ << "PuzzleWidget::dragLeaveEvent";
	QRect updateRect = highlightedRect;
	highlightedRect = QRect();
	update(updateRect);
	event->accept();
}

void PuzzleWidget::dragMoveEvent(QDragMoveEvent *event)
{
qDebug() << __FILE__ << "PuzzleWidget::dragMoveEvent";
	QRect updateRect = highlightedRect.unite(targetSquare(event->pos()));
	
	if (event->mimeData()->hasFormat("image/x-puzzle-piece") && findPiece(targetSquare(event->pos())) == -1)
	{
		highlightedRect = targetSquare(event->pos());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		highlightedRect = QRect();
		event->ignore();
	}
	
	update(updateRect);
}

void PuzzleWidget::dropEvent(QDropEvent *event)
{
qDebug() << __FILE__ << "PuzzleWidget::dropEvent";
	if (event->mimeData()->hasFormat("image/x-puzzle-piece") && findPiece(targetSquare(event->pos())) == -1)
	{
		QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);	
		QRect square = targetSquare(event->pos());
		QPixmap pixmap;
		QPoint location;
		dataStream >> pixmap >> location;

		pieceLocations.append(location);
		piecePixmaps.append(pixmap);
		pieceRects.append(square);
		
		highlightedRect = QRect();
		update(square);

		event->setDropAction(Qt::MoveAction);
		event->accept();

		if (location == QPoint(square.x() / PIECE_SIZE, square.y() / PIECE_SIZE))
		{
			inPlace ++;
			
			if (inPlace == 25)
			{
				emit puzzleCompleted();
			}
		}
	}
	else
	{
		highlightedRect = QRect();
		event->ignore();
	}
}

void PuzzleWidget::mousePressEvent(QMouseEvent *event)
{
qDebug() << __FILE__ << "PuzzleWidget::mousePressEvent";
	QRect square = targetSquare(event->pos());
	int found = findPiece(square);
	
	if (found == -1)
	{
		return;
	}
	
	QPoint location = pieceLocations[found];
	QPixmap pixmap = piecePixmaps[found];
	pieceLocations.removeAt(found);
	piecePixmaps.removeAt(found);
	pieceRects.removeAt(found);
	
	if (location == QPoint(square.x() / PIECE_SIZE, square.y() / PIECE_SIZE))
	{
		inPlace--;
	}

	update(square);

	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	
	dataStream << pixmap << location;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("image/x-puzzle-piece", itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);	
	drag->setHotSpot(event->pos() - square.topLeft());
	drag->setPixmap(pixmap);
	
	if ((drag->exec(Qt::MoveAction) == Qt::MoveAction) == false)
	{
		pieceLocations.insert(found, location);
		piecePixmaps.insert(found, pixmap);
		pieceRects.insert(found, square);
		update(targetSquare(event->pos()));
		
		if (location == QPoint(square.x() / PIECE_SIZE, square.y() / PIECE_SIZE))
		{
			inPlace++;
		}
	}
}

void PuzzleWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.fillRect(event->rect(), Qt::white);
	
	if (highlightedRect.isValid())
	{
		painter.setBrush(QColor("#ffcccc"));
		painter.setPen(Qt::NoPen);
		painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
	}

	for (int i=0; i< pieceRects.size(); ++i)
	{
		painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
	}

	painter.end();
}

int PuzzleWidget::findPiece(const QRect &pieceRect) const
{
	for (int i=0; i<pieceRects.size(); ++i)
	{
		if (pieceRect == pieceRects[i])
		{
			return i;
		}
	}

	return -1;
}

// position 所在的矩形
const QRect PuzzleWidget::targetSquare(const QPoint &position) const
{
	return QRect(position.x() / PIECE_SIZE * PIECE_SIZE, position.y() / PIECE_SIZE * PIECE_SIZE, PIECE_SIZE, PIECE_SIZE);
}
