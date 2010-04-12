#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QTabWidget>

class QDialogButtonBox;
class QFileInfo;
class QtabWidget;

class GeneralTab : public QWidget
{
	Q_OBJECT
	
	public:
		GeneralTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};

class PermissionTab : public QWidget
{
	Q_OBJECT
	
	public:
		PermissionTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};

class ApplicationTab : public QWidget
{
	Q_OBJECT
	
	public:
		ApplicationTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};

class TabDialog : public QDialog
{
	Q_OBJECT
	
	public:
		TabDialog(const QString &fileName, QWidget *parent = 0);

	private:
		QTabWidget *tabWidget;
		QDialogButtonBox *buttonBox;
};

#endif
