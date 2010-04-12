#include "window.h"
#include "mysortfilterproxymodel.h"

#include <QtGui>

Window::Window()
{
	proxyModel = new MySortFilterProxyModel(this);
	proxyModel->setDynamicSortFilter(true);

	sourceView = new QTreeView;
	sourceView->setRootIsDecorated(false);
	sourceView->setAlternatingRowColors(true);

	QHBoxLayout *sourceLayout = new QHBoxLayout;
	sourceLayout->addWidget(sourceView);
	sourceGroupBox = new QGroupBox("Original Model");
	sourceGroupBox->setLayout(sourceLayout);

	filterCaseSensitivityCheckBox = new QCheckBox("Case sensitive filter");
	filterCaseSensitivityCheckBox->setChecked(false);

	filterPatternLineEdit = new QLineEdit;
	filterPatternLineEdit->setText("Grace|Sports");
	
	filterPatternLabel = new QLabel("Filter pattern");
	filterPatternLabel->setBuddy(filterPatternLineEdit);

	filterSyntaxComboBox = new QComboBox;
	filterSyntaxComboBox->addItem("Regular expression", QRegExp::RegExp);	
	filterSyntaxComboBox->addItem("Wildcard", QRegExp::Wildcard);	
	filterSyntaxComboBox->addItem("Fixed string", QRegExp::FixedString);	
	
	fromDateEdit = new QDateEdit;
	fromDateEdit->setDate(QDate(1970, 01, 01));	
	fromLabel = new QLabel("From");
	fromLabel->setBuddy(fromDateEdit);

	toDateEdit = new QDateEdit;
	toDateEdit->setDate(QDate(2099, 12, 31));	
	toLabel = new QLabel("To");
	toLabel->setBuddy(toDateEdit);
	
	connect(filterPatternLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(textFilterChanged()));	
	connect(filterSyntaxComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(textFilterChanged()));	
	connect(filterCaseSensitivityCheckBox, SIGNAL(toggled(const QString &)), this, SLOT(textFilterChanged()));	
	connect(fromDateEdit, SIGNAL(dateChanged(const QDate &)), this, SLOT(dateFilterChanged()));	
	connect(toDateEdit, SIGNAL(dateChanged(const QDate &)), this, SLOT(dateFilterChanged()));	

	proxyView = new QTreeView;
	proxyView->setRootIsDecorated(false);
	proxyView->setAlternatingRowColors(true);
	proxyView->setModel(proxyModel);
	proxyView->setSortingEnabled(true);
	proxyView->sortByColumn(1, Qt::AscendingOrder);

	QGridLayout *proxyLayout = new QGridLayout;
	proxyLayout->addWidget(proxyView, 0, 0, 1, 3);	
	proxyLayout->addWidget(filterPatternLabel, 1, 0);	
	proxyLayout->addWidget(filterPatternLineEdit, 1, 1);	
	proxyLayout->addWidget(filterSyntaxComboBox, 1, 2);	
	proxyLayout->addWidget(filterCaseSensitivityCheckBox, 2, 0, 1, 3);	
	proxyLayout->addWidget(fromLabel, 3, 0);	
	proxyLayout->addWidget(fromDateEdit, 3, 1, 1, 2);	
	proxyLayout->addWidget(toLabel, 4, 0);	
	proxyLayout->addWidget(toDateEdit, 4, 1, 1, 2);	
	
	proxyGroupBox = new QGroupBox("Sorted / Filtered Model");
	proxyGroupBox->setLayout(proxyLayout);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(sourceGroupBox);
	mainLayout->addWidget(proxyGroupBox);
	setLayout(mainLayout);
	
	setWindowTitle("Custom Sort / Filter Model");
	resize(500, 450);
}

void Window::setSourceModel(QAbstractItemModel *model)
{
	proxyModel->setSourceModel(model);
	sourceView->setModel(model);
}

void Window::textFilterChanged()
{
	QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(filterSyntaxComboBox->itemData(filterSyntaxComboBox->currentIndex()).toInt());
	Qt::CaseSensitivity cs = filterCaseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

	QRegExp regExp(filterPatternLineEdit->text(), cs, syntax);
	proxyModel->setFilterRegExp(regExp);
}

void Window::dateFilterChanged()
{
	proxyModel->setFilterMinimumDate(fromDateEdit->date());
	proxyModel->setFilterMaximumDate(toDateEdit->date());
}

