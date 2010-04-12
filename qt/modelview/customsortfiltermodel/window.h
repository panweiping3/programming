#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QAbstractItemModel;
class QCheckBox;
class QComboBox;
class QDateEdit;
class QGroupBox;
class QLabel;
class QLineEdit;
class QTreeView;

class MySortFilterProxyModel;

class Window : public QWidget
{
	Q_OBJECT
	
	public:
		Window();
	
		void setSourceModel(QAbstractItemModel *model);

	private slots:
		void textFilterChanged();
		void dateFilterChanged();

	private:
		MySortFilterProxyModel *proxyModel;
		
		QGroupBox *sourceGroupBox;
		QGroupBox *proxyGroupBox;
		QTreeView *sourceView;
		QTreeView *proxyView;
		QCheckBox *filterCaseSensitivityCheckBox;
		QLabel *filterPatternLabel;
		QLabel *fromLabel;
		QLabel *toLabel;
		QLineEdit *filterPatternLineEdit;
		QComboBox *filterSyntaxComboBox;
		QDateEdit *fromDateEdit;
		QDateEdit *toDateEdit;
};

#endif
