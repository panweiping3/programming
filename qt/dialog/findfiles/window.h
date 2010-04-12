#ifndef WINDOW_H 
#define WINDOW_H

#include <QDialog>
#include <QDir>

class QComboBox;
class QLabel;
class QPushButton;
class QTabelWidget;
class QDir;
class QStringList;
class QTableWidget;
 
class Window : public QDialog
{
	Q_OBJECT
	
	public:
		Window(QWidget *parent = 0);
	
	private slots:
		void browse();
		void find();
		void openFileOfItem(int row, int column);
		
	private:
		QStringList findFiles(const QStringList &files, const QString &text);
		void showFiles(const QStringList &files);
		QPushButton *createButton(const QString &text, const char *member);
		QComboBox *createComboBox(const QString &text = QString());
		void updateComboBox(QComboBox *comboBox);
		void createFilesTable();
	
		QComboBox *fileComboBox;
		QComboBox *textComboBox;
		QComboBox *directoryComboBox;
		
		QLabel *fileLabel;
		QLabel *textLabel;
		QLabel *directoryLabel;
		QLabel *filesFoundLabel;
		
		QPushButton *browseButton;
		QPushButton *findButton;
		QTableWidget *filesTable;
	
		QDir currentDir;	
};

#endif
