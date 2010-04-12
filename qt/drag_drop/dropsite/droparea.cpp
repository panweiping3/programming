#include "droparea.h"

#include <QtGui>

DropArea::DropArea(QWidget *parent)
	: QLabel(parent)
{
	setMinimumSize(200, 200);
	setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
	setAlignment(Qt::AlignCenter);
	setAcceptDrops(true);
	setAutoFillBackground(true);
	clear();
}

void DropArea::clear()
{
	setText("drop content");
	setBackgroundRole(QPalette::Dark);
	
	emit changed();
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)	
{
	setText("drop content");
	setBackgroundRole(QPalette::Highlight);
	
	event->acceptProposedAction();
	emit changed(event->mimeData());
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
	clear();
	event->accept();	
}

void DropArea::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	
	if (mimeData->hasImage())
	{
		setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
	}
	else if (mimeData->hasHtml())
		{
			setText(mimeData->html());
			setTextFormat(Qt::RichText);
		}
		else if (mimeData->hasText())
			{
				setText(mimeData->text());
				setTextFormat(Qt::PlainText);
			}
			else if (mimeData->hasUrls())
				{
					QList <QUrl> urlList = mimeData->urls();
					QString text;
					for (int i=0; i<urlList.size() && i < 32; ++i)
					{
						QString url = urlList.at(i).path();
						text += url + QString("\n");
					}
		
					setText(text);
				}
				else if (mimeData->hasImage())
				{
						QByteArray itemData = qvariant_cast<QByteArray>(event->mimeData()->imageData());
						QDataStream dataStream(&itemData, QIODevice::ReadOnly);

						QPixmap pixmap;
						QPoint offset;
						dataStream >> pixmap >> offset;

						setPixmap(pixmap);
						move(event->pos() - offset);
				}

	setBackgroundRole(QPalette::Dark);	
	event->acceptProposedAction();	
}
