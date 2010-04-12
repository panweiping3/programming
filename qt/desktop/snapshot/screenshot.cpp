#include <QtGui>

#include "screenshot.h"

Screenshot::Screenshot()
{
	screenshotLabel = new QLabel;
	screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);	
	screenshotLabel->setAlignment(Qt::AlignCenter);
	screenshotLabel->setMinimumSize(240, 160);
	
	createOptionsGroupBox();
	createButtonsLayout();
	
	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(screenshotLabel);
	mainLayout->addWidget(optionsGroupBox);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);

	shootScreen();
	delaySpinBox->setValue(5);
	
	setWindowTitle("Screenshot");
	resize(300, 200);
}

void Screenshot::resizeEvent(QResizeEvent *event)
{
	QSize scaledSize = originalPixmap.size();
	scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
	
	// 如无必要，不刷新图像
	if ((screenshotLabel->pixmap() == 0) || (scaledSize != screenshotLabel->pixmap()->size()))
	{
		updateScreenshotLabel();
	}	
}

void Screenshot::newScreenshot()
{
	if (hideThisWindowCheckBox->isChecked())
	{
		hide();	
	}

	newScreenshotButton->setDisabled(true);
	
	QTimer::singleShot(delaySpinBox->value() * 1000, this, SLOT(shootScreen()));
}

void Screenshot::saveScreenshot()
{
	QString format = "png";
	QString initialPath = QDir::currentPath() + QString("/untitled.") + format;
	
	QString fileName = QFileDialog::getSaveFileName(this,
												tr("Save As"),
												initialPath,
												tr("%1 Files (*.%2);;All Files(*)")
												.arg(format.toUpper())
												.arg(format));

	if (fileName.isEmpty() == false)
	{
		originalPixmap.save(fileName, format.toAscii());
	}
}

void Screenshot::shootScreen()
{
	if (delaySpinBox->value() != 0)
	{
		qApp->beep();
	}

	originalPixmap = QPixmap();
	originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
	updateScreenshotLabel();

	newScreenshotButton->setDisabled(false);
	
	if (hideThisWindowCheckBox->isChecked())
	{
		show();
	}
}

void Screenshot::updateCheckBox()
{
	if (delaySpinBox->value() == 0)
	{
		hideThisWindowCheckBox->setDisabled(true);
	}
	else
	{
		hideThisWindowCheckBox->setDisabled(false);
	}
}

void Screenshot::createOptionsGroupBox()
{
	optionsGroupBox = new QGroupBox("Options");
	
	delaySpinBox = new QSpinBox;
	delaySpinBox->setSuffix("s");
	delaySpinBox->setMaximum(60);
	
	connect(delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCheckBox()));

	delaySpinBoxLabel = new QLabel("Screenshot delay");
	
	hideThisWindowCheckBox = new QCheckBox("hide this window");
	
	optionsGroupBoxLayout = new QGridLayout;
	optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
	optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);
	optionsGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1, 2);
	optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

void Screenshot::createButtonsLayout()
{
	newScreenshotButton = createButton("New Screenshot", this, SLOT(newScreenshot()));
	saveScreenshotButton = createButton("Save Screenshot", this, SLOT(saveScreenshot()));
	
	quitScreenshotButton = createButton("Quit", this, SLOT(close()));
	
	buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(newScreenshotButton);
	buttonsLayout->addWidget(saveScreenshotButton);
	buttonsLayout->addWidget(quitScreenshotButton);
}

QPushButton *Screenshot::createButton(const QString &text, QWidget *receiver, const char *member)
{
	QPushButton *button = new QPushButton(text);
	button->connect(button, SIGNAL(clicked()), receiver, member);
	return button;
}

void Screenshot::updateScreenshotLabel()
{
	screenshotLabel->setPixmap(	originalPixmap.scaled(screenshotLabel->size(), 
								Qt::KeepAspectRatio,
								Qt::SmoothTransformation));
}
