#include "droparea.h"
#include "dropsitewidget.h"

#include <QtGui>

DropSiteWindow::DropSiteWindow()
{
	abstractLabel = new QLabel("This example accepts drags from other applications and displays the MIME types provided by the drag object");
	abstractLabel->setWordWrap(true);
	abstractLabel->adjustSize();
	
	dropArea = new DropArea;
	connect(dropArea,  SIGNAL(changed(const QMimeData *)), this, SLOT(updateFormatsTable(const QMimeData *)));

	QStringList labels;
	labels << "Format" << "Content";
	
	formatsTable = new QTableWidget;
	formatsTable->setColumnCount(2);
	formatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	formatsTable->setHorizontalHeaderLabels(labels);
	formatsTable->horizontalHeader()->setStretchLastSection(true);

	clearButton = new QPushButton("Clear");
	quitButton = new QPushButton("Quit");
	
	buttonBox = new QDialogButtonBox;
	buttonBox->addButton(clearButton, QDialogButtonBox::ActionRole);	
	buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

	connect(quitButton, SIGNAL(pressed()), this, SLOT(close()));
	connect(clearButton, SIGNAL(pressed()), dropArea,  SLOT(clear()));
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(abstractLabel);
	mainLayout->addWidget(dropArea);
	mainLayout->addWidget(formatsTable);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);
	setWindowTitle("Drop Site");
	setMinimumSize(350, 500);
}

void DropSiteWindow::updateFormatsTable(const QMimeData *mimeData)
{
	//formatsTable->setRowCount(0);
	
	if (mimeData == NULL)
	{
		return;
	}

	QTableWidgetItem *formatItem = new QTableWidgetItem();
	formatItem->setFlags(Qt::ItemIsEnabled);
	formatItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
	QString text;
	QString format;

	if (mimeData->hasText())
	{
			text = mimeData->text().simplified();
			format = "text/plain";	
	}
	else if (mimeData->hasHtml())
		{
			text = mimeData->html().simplified();
			format = "text/html";	
		}
		else if (mimeData->hasImage())
		{
			QByteArray data = mimeData->data(format);

			for (int i=0; i<data.size() && i<32; ++i)
			{
				QString hex = QString("%1").arg(uchar(data[i]), 2, 16, QChar('0')).toUpper();
				text.append(hex + " ");
			}

			format = "image/ *";	
		}


	qDebug() << text;
	qDebug() << format;

	int row = formatsTable->rowCount();
	formatsTable->insertRow(row);
	formatsTable->setItem(row, 0, new QTableWidgetItem(format));	
	formatsTable->setItem(row, 1, new QTableWidgetItem(text));	

	formatsTable->resizeColumnToContents(row);
}

