#include <QtGui>
#include "sort_dialog.h"

SortDialog::SortDialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);	
//	setLayout(gridLayout);	
	groupBox_2->hide();
	groupBox_3->hide();
	//layout()->setSizeConstraint(QLayout::SetFixedSize);

	setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
	comboBox->clear();
	comboBox_3->clear();
	comboBox_5->clear();
	comboBox_3->addItem(tr("None"));
	comboBox_5->addItem(tr("None"));
	comboBox->setMinimumSize(comboBox_3->sizeHint());
	
	QChar ch = first;
	
	while (ch <= last)
	{
		comboBox->addItem(QString(ch));
		comboBox_3->addItem(QString(ch));
		comboBox_5->addItem(QString(ch));
		ch = ch.unicode() + 1;
	}
}
