#include "window.h"

#include <QtGui>

Window::Window(QWidget *parent)
	: QDialog(parent)
{
	findButton = createButton("&Find", SLOT(find()));
	findButton->setDefault(true);

	browseButton = createButton("&Browse...", SLOT(browse()));
	
	fileComboBox = createComboBox("*");
	textComboBox = createComboBox();
	directoryComboBox = createComboBox(QDir::currentPath());

	fileLabel = new QLabel("Named:");
	textLabel = new QLabel("containing text:");
	directoryLabel = new QLabel("In directory");
	filesFoundLabel = new QLabel;

	createFilesTable();
	
	QHBoxLayout	*buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(findButton);
	
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(fileLabel, 0, 0);
	mainLayout->addWidget(fileComboBox, 0, 1, 1,2);
	mainLayout->addWidget(textLabel, 1, 0);
	mainLayout->addWidget(textComboBox, 1, 1, 1,2);
	mainLayout->addWidget(directoryLabel, 2, 0);
	mainLayout->addWidget(directoryComboBox, 2, 1);
	mainLayout->addWidget(browseButton, 2, 2);
	mainLayout->addWidget(filesTable, 3, 0, 1, 3);
	mainLayout->addWidget(filesFoundLabel, 4, 0);
	mainLayout->addLayout(buttonsLayout, 5, 0, 1, 3);

	setLayout(mainLayout);
	
	setWindowTitle("Find Files");
	
	resize(700, 300);
}

void Window::browse()
{
	QString directory = QFileDialog::getExistingDirectory(this, "Find Files", QDir::currentPath());
	if (directory.isEmpty() == false)
	{
		if (directoryComboBox->findText(directory) == -1)
		{
			directoryComboBox->addItem(directory);
		}
		
		directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
	}
}

void Window::find()
{
	filesTable->setRowCount(0);
	
	QString fileName = fileComboBox->currentText();
	QString text = textComboBox->currentText();
	QString path = directoryComboBox->currentText();
	
	updateComboBox(fileComboBox);
	updateComboBox(textComboBox);
	updateComboBox(directoryComboBox);

	currentDir = QDir(path);
	QStringList files;
	
	if (fileName.isEmpty() == true)
	{
		fileName = "*";
	}
	
	files = currentDir.entryList(QStringList(fileName), QDir::Files | QDir::NoSymLinks);	
	
	if (text.isEmpty() == false)
	{
		files = findFiles(files, text);
	}
	
	showFiles(files);
}

QStringList Window::findFiles(const QStringList &files, const QString &text)
{
	QProgressDialog progressDialog(this);
	progressDialog.setCancelButtonText("&Cancel");
	progressDialog.setRange(0, files.size());
	progressDialog.setWindowTitle("Find Files");

	QStringList foundFiles;
	
	for (int i=0; i<files.size(); ++i)
	{
		progressDialog.setValue(i);
		progressDialog.setLabelText(tr("Searching file number %1 of %2...")
									.arg(i)
									.arg(files.size())
									);
		qApp->processEvents();
			
		if (progressDialog.wasCanceled())
		{
			break;
		}

		QFile file(currentDir.absoluteFilePath(files[i]));
	
		if (file.open(QIODevice::ReadOnly))
		{
			QString line;
			QTextStream in(&file);
			
			while (in.atEnd() != true)
			{
				if (progressDialog.wasCanceled())
				{
					break;
				}
	
				line = in.readLine();
				
				if (line.contains(text))
				{
					foundFiles << files[i];
					break;
				}
			}
		}
	}
	
	return foundFiles;	
}

void Window::showFiles(const QStringList &files)
{
	for (int i=0; i<files.size(); ++i)
	{
		QFile file(currentDir.absoluteFilePath(files[i]));
		qint64 size = QFileInfo(file).size();
		
		QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);
		fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
		QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB")
														.arg(int((size + 1023) / 1024)));
		
		sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);
	
		int row = filesTable->rowCount();
		filesTable->insertRow(row);
		filesTable->setItem(row, 0, fileNameItem);
		filesTable->setItem(row, 1, sizeItem);
	}
		
	filesFoundLabel->setText(tr("%1 file(s) found")
							.arg(files.size())
							+ " Double click to open it");
}

QPushButton *Window::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
		
	connect(button, SIGNAL(clicked()), this, member);
		
	return button;
}

QComboBox *Window::createComboBox(const QString &text)
{
	QComboBox *comboBox = new QComboBox;
	comboBox->setEditable(true);
	comboBox->addItem(text);
	comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	return comboBox;
}

void Window::createFilesTable()
{
	filesTable = new QTableWidget(0, 2);
	filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	QStringList labels;
	labels << tr("File Name") << tr("Size");
	filesTable->setHorizontalHeaderLabels(labels);
	filesTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	//filesTable->verticalHeader()->hide();
	filesTable->setShowGrid(false);
	
	connect(filesTable, SIGNAL(cellActivated(int, int)), this, SLOT(openFileOfItem(int, int)));
}

void Window::openFileOfItem(int row, int column)
{
	QTableWidgetItem *item = filesTable->item(row, 0);

	QDesktopServices::openUrl(currentDir.absoluteFilePath(item->text()));
}

void Window::updateComboBox(QComboBox *comboBox)
{
	if (comboBox->findText(comboBox->currentText()) == -1)
	{
		comboBox->addItem(comboBox->currentText());
	}
}

