#ifndef REGEXPDIALOG_H
#define REGEXPDIALOG_H

#include <QDialog>

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;

class RegExpDialog : public QDialog
{
	Q_OBJECT

	public:
		RegExpDialog(QWidget *parent =0);

	private slots:
		void refresh();
	
	private:
		QLabel *patternLabel;
		QLabel *escapedPatternLabel;
		QLabel *syntaxLabel;
		QLabel *textLabel;
		QComboBox *patternComboBox;
		QLineEdit *escapedPatternLineEdit;
		QComboBox *textComboBox;
		QCheckBox *caseSensitiveCheckBox;
		QCheckBox *minimalCheckBox;
		QComboBox *syntaxComboBox;

		QLabel *indexLabel;
		QLabel *matchedLengthLabel;
		QLineEdit *indexEdit;
		QLineEdit *matchedLengthEdit;

		enum { MaxCaptures = 6 };	
		QLabel *captureLabels[MaxCaptures];
		QLineEdit *captureEdits[MaxCaptures];	
};

#endif
