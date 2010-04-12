#include "finddialog.h"

#include <QtGui>

FindDialog::FindDialog(QWidget *parent)
	: QDialog(parent)
{
	label = new QLabel("Find & What:");	
	lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);	

	caseCheckBox = new QCheckBox("Match&case");
	fromStartCheckBox = new QCheckBox("Search form &start");
	fromStartCheckBox->setChecked(true);
	
	findButton = new QPushButton("&Find");
	findButton->setDefault(true);
	
	moreButton = new QPushButton("&More");
	moreButton->setCheckable(true);
	moreButton->setAutoDefault(false);
	
	buttonBox = new QDialogButtonBox(Qt::Vertical);	
	buttonBox->addButton(findButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(moreButton, QDialogButtonBox::ActionRole);

	extension = new QWidget;
	
	wholeWordsCheckBox = new QCheckBox("&Whole words");
	backwardCheckBox = new QCheckBox("Search &backward");
	searchSelectionCheckBox = new QCheckBox("Search se&lection");
	
	//connect(moreButton, SIGNAL(toggled(bool)), extension, SLOT(setVisible(bool)));
	connect(moreButton, SIGNAL(clicked(bool)), extension, SLOT(setVisible(bool)));
	
	QVBoxLayout *extensionLayout = new QVBoxLayout;
	extensionLayout->setMargin(0);
	extensionLayout->addWidget(wholeWordsCheckBox);
	extensionLayout->addWidget(backwardCheckBox);
	extensionLayout->addWidget(searchSelectionCheckBox);

	extension->setLayout(extensionLayout);
	
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);	

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(fromStartCheckBox);
	leftLayout->addStretch(1);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);	
	mainLayout->addLayout(leftLayout, 0, 0);
	mainLayout->addWidget(buttonBox, 0, 1);
	mainLayout->addWidget(extension, 1, 0, 1, 2);
	setLayout(mainLayout);
	
	setWindowTitle("Extension");
	resize(800, 600);
	extension->hide();
}

