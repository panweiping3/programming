#include "regexpdialog.h"

#include <QtGui>

RegExpDialog::RegExpDialog(QWidget *parent)
{
	patternComboBox = new QComboBox;
	patternComboBox->setEditable(true);
	patternComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	
	patternLabel = new QLabel("Pattern");
	patternLabel->setBuddy(patternComboBox);

	escapedPatternLineEdit = new QLineEdit;
	escapedPatternLineEdit->setReadOnly(true);
	QPalette palette = escapedPatternLineEdit->palette();
	palette.setBrush(QPalette::Base, palette.brush(QPalette::Disabled, QPalette::Base));
	escapedPatternLineEdit->setPalette(palette);

	escapedPatternLabel = new QLabel("Escaped Pattern");
	escapedPatternLabel->setBuddy(escapedPatternLineEdit);
	
	syntaxComboBox = new QComboBox;
	syntaxComboBox->addItem("Regular expression v1", QRegExp::RegExp);
	syntaxComboBox->addItem("Regular expression v2", QRegExp::RegExp2);
	syntaxComboBox->addItem("Wildcard", QRegExp::Wildcard);
	syntaxComboBox->addItem("Fixed string", QRegExp::FixedString);
		
	syntaxLabel = new QLabel("Pattern syntax");
	syntaxLabel->setBuddy(syntaxComboBox);

	textComboBox = new QComboBox;
	textComboBox->setEditable(true);
	textComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	textLabel = new QLabel("Text");
	textLabel->setBuddy(textComboBox);
	
	caseSensitiveCheckBox = new QCheckBox("Case Sensitive");
	caseSensitiveCheckBox->setChecked(true);
	minimalCheckBox = new QCheckBox("Minimum");
	
	indexLabel = new QLabel("Index of Match");
	indexEdit = new QLineEdit;
	indexEdit->setReadOnly(true);
	
	matchedLengthLabel = new QLabel("Matched Length");
	matchedLengthEdit = new QLineEdit;
	matchedLengthEdit->setReadOnly(true);
	
	for (int i=0; i<MaxCaptures; ++i)
	{
		captureLabels[i] = new QLabel(tr("Capture %1").arg(i));
		captureEdits[i] = new QLineEdit;
		captureEdits[i]->setReadOnly(true);
	}	
	captureLabels[0]->setText("Match:");
	
	QHBoxLayout *checkBoxLayout = new QHBoxLayout;
	checkBoxLayout->addWidget(caseSensitiveCheckBox);
	checkBoxLayout->addWidget(minimalCheckBox);
	checkBoxLayout->addStretch(1);	
	
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(patternLabel, 0, 0);
	mainLayout->addWidget(patternComboBox, 0, 1);
	mainLayout->addWidget(escapedPatternLabel, 1, 0);
	mainLayout->addWidget(escapedPatternLineEdit, 1, 1);
	mainLayout->addWidget(syntaxLabel, 2, 0);
	mainLayout->addWidget(syntaxComboBox, 2, 1);
	mainLayout->addLayout(checkBoxLayout, 3, 0, 1, 2);
	mainLayout->addWidget(textLabel, 4, 0);
	mainLayout->addWidget(textComboBox, 4, 1);
	mainLayout->addWidget(indexLabel, 5, 0);
	mainLayout->addWidget(indexEdit, 5, 1);
	mainLayout->addWidget(matchedLengthLabel, 6, 0);
	mainLayout->addWidget(matchedLengthEdit, 6, 1);

	for (int j = 0; j < MaxCaptures; ++j)
	{
		mainLayout->addWidget(captureLabels[j], 7 + j, 0);
		mainLayout->addWidget(captureEdits[j], 7 + j, 1);
	}	

	setLayout(mainLayout);

	connect(patternComboBox, SIGNAL(editTextChanged(const QString &)), this, SLOT(refresh()));
	connect(textComboBox, SIGNAL(editTextChanged(const QString &)), this, SLOT(refresh()));
	connect(caseSensitiveCheckBox, SIGNAL(toggled(bool)), this, SLOT(refresh()));
	connect(minimalCheckBox, SIGNAL(toggled(bool)), this, SLOT(refresh()));
	connect(syntaxComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refresh()));

	patternComboBox->addItem("[A-Za-z]+([A-Za-z_0-9]*)");
	textComboBox->addItem("(10 + delta4) * 32");	
	
	setWindowTitle("RegExp");
	setFixedHeight(sizeHint().height());
	
	refresh();
}

void RegExpDialog::refresh()
{
	setUpdatesEnabled(false);
	
	QString pattern = patternComboBox->currentText();
	QString text = textComboBox->currentText();
	
	QString escaped = pattern;
	escaped.replace("\\", "\\\\");
	escaped.replace("\"", "\\\"");
	escaped.prepend("\"");
	escaped.append("\"");
	escapedPatternLineEdit->setText(escaped);

	QRegExp rx(pattern);
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
	
	if (caseSensitiveCheckBox->isChecked())
	{
		cs = Qt::CaseSensitive;
	}
	
	rx.setCaseSensitivity(cs);
	rx.setMinimal(minimalCheckBox->isChecked());	
	
	QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(syntaxComboBox->itemData(syntaxComboBox->currentIndex()).toInt());
	
	rx.setPatternSyntax(syntax);

	QPalette palette = patternComboBox->palette();
	if (rx.isValid())
	{
		palette.setColor(QPalette::Text, textComboBox->palette().color(QPalette::Text));
	}
	else
	{
		palette.setColor(QPalette::Text, Qt::red);
	}
	patternComboBox->setPalette(palette);
	
	indexEdit->setText(QString::number(rx.indexIn(text)));
	matchedLengthEdit->setText(QString::number(rx.matchedLength()));
	
	for (int i = 0; i < MaxCaptures; ++i)
	{
		captureLabels[i]->setEnabled(i <= rx.numCaptures());
		captureEdits[i]->setEnabled(i <= rx.numCaptures());
		captureEdits[i]->setText(rx.cap(i));
	}

	setUpdatesEnabled(true);
}
