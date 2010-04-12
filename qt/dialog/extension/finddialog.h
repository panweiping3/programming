#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QLabel;
class QCheckBox;
class QDialogButtonBox;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
{
	Q_OBJECT
	
	public:
		FindDialog(QWidget *parent = 0);
	
	private:
		QLabel *label;
		QLineEdit *lineEdit;
		QCheckBox *caseCheckBox;
		QCheckBox *fromStartCheckBox;
		QCheckBox *wholeWordsCheckBox;
		QCheckBox *searchSelectionCheckBox;
		QCheckBox *backwardCheckBox;
		QDialogButtonBox *buttonBox;
		QPushButton *findButton;
		QPushButton *moreButton;
		QWidget *extension;
};

#endif
