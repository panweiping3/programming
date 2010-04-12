#include <QtGui> 
#include <QMessageBox> 
#include "finddialog.h" 


FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{
	label = new QLabel(tr("Find &what:"));
	lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);
	caseCheckBox = new QCheckBox(tr("Match &case"));
	backwardCheckBox = new QCheckBox(tr("Search &backward"));
	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	findButton->setEnabled(false);
	closeButton = new QPushButton(tr("close"));
	connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
	connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);
	
	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(backwardCheckBox);

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(closeButton);
	
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Find"));
	setFixedHeight(sizeHint().height());

	QSettings settings("find dialog settings");
	QString caseString = settings.value("case selected", QString("CaseSensitive")).toString();
	QMessageBox::about(this, tr("last case selected"), caseString);
}

void FindDialog::findClicked()
{
	QString text = lineEdit->text();
	Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

	if (backwardCheckBox->isChecked())
	{
		emit findPrevious(text, cs);
	}
	else
	{
		emit findNext(text, cs);
	}

	int r = QMessageBox::warning(this, tr("result"), tr("ok or cancel?"), QMessageBox::Yes | QMessageBox::Default, QMessageBox::No);
	
	if (r == QMessageBox::No)
	{
		QMessageBox::about(this, tr("about"), tr("<p>I'll be closed and I'll save current settings</p>"));
		
		QSettings settings("find dialog settings");
		if (cs == Qt::CaseSensitive)
			settings.setValue("case selected", QString("CaseSensitive"));
		else
			settings.setValue("case selected", QString("CaseInsensitive"));

		close();	
	}
	
	return;
}

void FindDialog::enableFindButton(const QString &text)
{
	findButton->setEnabled(!text.isEmpty());
}
