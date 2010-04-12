#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QAbstractItemModel;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QSortFilterProxyModel;
class QTreeView;

class Window : public QWidget
{
	Q_OBJECT
	
	public:
		Window();
		
		void setSourceModel(QAbstractItemModel *model);
		
	private slots:
		void filterRegExpChanged();
		void filterColumnChanged();
		void sortChanged();

	private:
		QSortFilterProxyModel *proxyModel;
	
		QGroupBox *sourceGroupBox;
		QGroupBox *proxyGroupBox;
		QTreeView *sourceView;
		QTreeView *proxyView;
		QCheckBox *filterCaseSensitivityCheckBox;
		QCheckBox *sortCaseSensitivityCheckBox;	
		QLabel *filterPatternLabel;
		QLabel *filterSyntaxLabel;
		QLabel *filterColumnLabel;
		QLineEdit *filterPatternLineEdit;
		QComboBox *filterSyntaxComboBox;
		QComboBox *filterColumnComboBox;
};

#endif
