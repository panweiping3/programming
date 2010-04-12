#include "stylewindow.h"

#include <QtGui>

StyleWindow::StyleWindow()
{
	QPushButton *styledButton = new QPushButton(tr("Big Red Button"));
	
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(styledButton);

	QGroupBox *styleBox = new QGroupBox(tr("a simple style button"));
	styleBox->setLayout(layout);
	
	QGridLayout *outerLayout = new QGridLayout;
	outerLayout->addWidget(styleBox, 0, 0);
	setLayout(outerLayout);
	
	setWindowTitle(tr("Style Plugin Example"));
}
