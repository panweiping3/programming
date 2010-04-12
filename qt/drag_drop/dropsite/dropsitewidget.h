#ifndef DROPSITEWIDGET_H 
#define DROPSITEWIDGET_H

#include <QWidget>

class QDialogButtonBox;
class QLabel;
class QMimeData;
class QPushButton;
class QTableWidget;

class DropArea;

class DropSiteWindow : public QWidget
{
	Q_OBJECT
	
	public:
		DropSiteWindow();
	
	public slots:
		void updateFormatsTable(const QMimeData *mimeData);
	
	private:
		DropArea *dropArea;
		QLabel *abstractLabel;
		QTableWidget *formatsTable;
		QPushButton *clearButton;
		QPushButton *quitButton;
		QDialogButtonBox *buttonBox;
};

#endif

