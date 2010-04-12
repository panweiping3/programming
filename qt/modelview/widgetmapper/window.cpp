#include "window.h"

#include <QtGui>

Window::Window(QWidget *parent)
	:QWidget(parent)
{
	setupModel();
	
	nameLabel = new QLabel("Na&me:");
	nameEdit = new QLineEdit();
	nameLabel->setBuddy(nameEdit);
	addressLabel = new QLabel("&Address");
	addressEdit = new QTextEdit();
	addressLabel->setBuddy(addressEdit);
	ageLabel = new QLabel("A&ge (in years)");
	ageSpinBox = new QSpinBox();
	ageLabel->setBuddy(ageSpinBox);
	nextButton = new QPushButton("&Next");
	previousButton = new QPushButton("&Previous");

	mapper = new QDataWidgetMapper(this);
	mapper->setModel(model);
	mapper->addMapping(nameEdit, 0);
	mapper->addMapping(addressEdit, 1);
	mapper->addMapping(ageSpinBox, 2);
	
	connect(previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
	connect(nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
	connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(nameLabel, 0, 0, 1, 1);	
	layout->addWidget(nameEdit, 0, 1, 1, 1);	
	layout->addWidget(previousButton, 0, 2, 1, 1);	
	layout->addWidget(addressLabel, 1, 0, 1, 1);	
	layout->addWidget(addressEdit, 1, 1, 2, 1);	
	layout->addWidget(nextButton, 1, 2, 1, 1);	
	layout->addWidget(ageLabel, 3, 0, 1, 1);	
	layout->addWidget(ageSpinBox, 3, 1, 1, 1);	
	
	setLayout(layout);
		
	setWindowTitle("Simple Widget Mapper");
	mapper->toFirst();
}

void Window::updateButtons(int row)
{
	previousButton->setEnabled(row > 0);
	nextButton->setEnabled(row < model->rowCount() - 1);
}

void Window::setupModel()
{
	model = new QStandardItemModel(5, 3, this);
	
	QStringList names;
	names << "asdd " << "dsfasd" << "fgggggggg" << "ghf" << "ertdfb";
	
	QStringList address;
	address << "asdd " << "dsfasd" << "fgggggggg" << "ghf" << "ertdfb";

	QStringList ages;
	ages << "asdd " << "dsfasd" << "fgggggggg" << "ghf" << "ertdfb";

	for (int row = 0; row < 5; ++row)
	{
		QStandardItem *item = new QStandardItem(names[row]);
		model->setItem(row, 0, item);
		item = new QStandardItem(address[row]);
		model->setItem(row, 1, item);
		item = new QStandardItem(ages[row]);
		model->setItem(row, 2, item);
	}	
}
