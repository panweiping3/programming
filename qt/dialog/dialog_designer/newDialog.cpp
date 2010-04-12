#include <QtGui>
#include <QRegExpValidator>
#include "newDialog.h"

NewDialog::NewDialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);	
	QRegExp regExp("[1-9][0-9]{0,2}");
	
	lineEdit->setValidator(new QRegExpValidator(regExp, this));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(pushButton_2, SIGNAL(clicked()), this, SLOT(reject()));
	connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged(const QString &)));
	pushButton->setEnabled(false);
}

void NewDialog::lineEditTextChanged(const QString &)
{
	pushButton->setEnabled(lineEdit->hasAcceptableInput());
}
