#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

#include <QDialog>
#include "ui_gotoCell.h"

class NewDialog : public QDialog, public Ui::Dialog
{
	Q_OBJECT
	public:
		NewDialog(QWidget *parent=0);
	
	private slots:
		void lineEditTextChanged(const QString &);
};

#endif
