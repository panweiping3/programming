#include <QtGui>

#include "draglabel.h"
#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
	: QWidget(parent)
{
	QFile dictionaryFile(":/words.txt");
	if (dictionaryFile.exists() == false)
	{
		qDebug() << "words file doesn't exist";
		// 因为此时QT的时间循环尚未开始，故exit, quit, closeAllWindows 都不起作用。
		// qApp->exit(-1);
		// qApp->quit();
		// qApp->closeAllWindows();
		QTimer::singleShot(0, qApp, SLOT(quit()));
	}

	dictionaryFile.open(QIODevice::ReadOnly);
	QTextStream inputStream(&dictionaryFile);

	int x = 5;
	int y = 5;
	
	while (inputStream.atEnd() == false)
	{
		QString word;
		inputStream >> word;
		
		if (word.isEmpty() == false)
		{
			DragLabel *wordLabel = new DragLabel(word, this);
			wordLabel->move(x, y);
			wordLabel->show();
			
			x += wordLabel->width() + 2;
			if (x >= 195)
			{
				x = 5;
				y += wordLabel->height() + 2;
			}
		}
	}
	
	QPalette newPalette = palette();
	newPalette.setColor(QPalette::Window, Qt::yellow);
	setPalette(newPalette);

	// 接受鼠标拖拽， that's important!
	setAcceptDrops(true);
	setMinimumSize(400, qMax(200, y));
	setWindowTitle("Dragable Text");
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasText())
	{
		if (children().contains(event->source()))
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else
		{
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}

void DragWidget::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasText())
	{
		const QMimeData *mine = event->mimeData();
		QStringList pieces = mine->text().split(QRegExp("\\s+"), QString::SkipEmptyParts);
		
		QPoint position = event->pos();
		QPoint hotSpot;
		
		QList<QByteArray> hotSpotPos = mine->data("application/x-hotspot").split(' ');
		if (hotSpotPos.size() == 2)
		{
			hotSpot.setX(hotSpotPos.first().toInt());
			hotSpot.setY(hotSpotPos.last().toInt());
		}

		foreach (QString piece, pieces)
		{
			DragLabel *newLabel = new DragLabel(piece, this);
			newLabel->move(position - hotSpot);
			newLabel->show();
			position += QPoint(newLabel->width(), 0);
		}
		
		if (children().contains(event->source()))
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}					
		else
		{
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}
