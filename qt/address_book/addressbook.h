#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;

class AddressBook : public QWidget
{
	Q_OBJECT
	public:
		AddressBook(QWidget *parent = 0);

	public slots:
		void addContact();
		void submitContact();
		void cancel();

	private:
		QLineEdit *nameLine;
		QTextEdit *addressText;
		QPushButton *addButton;
		QPushButton *submitButton;
		QPushButton *cancelButton;
};

#endif
