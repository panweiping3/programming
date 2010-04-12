#include "window.h"

#include <QtGui>

Window::Window()
{
	proxyModel = new QSortFilterProxyModel;
	proxyModel->setDynamicSortFilter(true);
	
	sourceGroupBox = new QGroupBox("Original Model");
	proxyGroupBox = new QGroupBox("Sorted/FIltered Model");
	
	sourceView = new QTreeView;
	sourceView->setRootIsDecorated(false);
	sourceView->setAlternatingRowColors(true);

	proxyView = new QTreeView;
	proxyView->setRootIsDecorated(false);
	proxyView->setAlternatingRowColors(true);
	proxyView->setModel(proxyModel);
	proxyView->setSortingEnabled(true);

	sortCaseSensitivityCheckBox = new QCheckBox("Case Sensitive sorting");	
	filterCaseSensitivityCheckBox = new QCheckBox("Case Sensitive filter");

	filterPatternLineEdit = new QLineEdit;
	filterPatternLabel = new QLabel("&Filter pattern");
	filterPatternLabel->setBuddy(filterPatternLineEdit);

	filterSyntaxComboBox = new QComboBox;
	filterSyntaxComboBox->addItem("Regular expression", QRegExp::RegExp);
	filterSyntaxComboBox->addItem("Wildcard", QRegExp::Wildcard);
	filterSyntaxComboBox->addItem("Fixed string", QRegExp::FixedString);
	filterSyntaxLabel = new QLabel("Filter &syntax");
	filterSyntaxLabel->setBuddy(filterSyntaxComboBox);

	filterColumnComboBox = new QComboBox;
	filterColumnComboBox->addItem("Subject");
	filterColumnComboBox->addItem("Sender");
	filterColumnComboBox->addItem("Date");
	filterColumnLabel = new QLabel("Filter &column");
	filterColumnLabel->setBuddy(filterColumnComboBox);

	connect(filterPatternLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(filterRegExpChanged()));	
	connect(filterSyntaxComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(filterRegExpChanged()));	
	connect(filterColumnComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(filterColumnChanged()));	
	connect(filterCaseSensitivityCheckBox, SIGNAL(toggled(bool)), this, SLOT(filterRegExpChanged()));	
	connect(sortCaseSensitivityCheckBox, SIGNAL(toggled(bool)), this, SLOT(sortChanged()));	

	QHBoxLayout *sourceLayout = new QHBoxLayout;
	sourceLayout->addWidget(sourceView);
	sourceGroupBox->setLayout(sourceLayout);
	
	QGridLayout *proxyLayout = new QGridLayout;	
	proxyLayout->addWidget(proxyView, 0, 0, 1, 3);
	proxyLayout->addWidget(filterPatternLabel, 1, 0);
	proxyLayout->addWidget(filterPatternLineEdit, 1, 1);
	proxyLayout->addWidget(filterSyntaxLabel, 2, 0);
	proxyLayout->addWidget(filterSyntaxComboBox, 2, 1, 1, 2);
	proxyLayout->addWidget(filterColumnLabel, 3, 0);
	proxyLayout->addWidget(filterColumnComboBox, 3, 1, 1, 2);
	proxyLayout->addWidget(filterCaseSensitivityCheckBox, 4, 0, 1, 2);
	proxyLayout->addWidget(sortCaseSensitivityCheckBox, 4, 2);
	proxyGroupBox->setLayout(proxyLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(sourceGroupBox);
	mainLayout->addWidget(proxyGroupBox);
	setLayout(mainLayout);
	
	setWindowTitle("Basic / Sorted Model");
	resize(500, 450);
		
	proxyView->sortByColumn(1, Qt::AscendingOrder);
	filterColumnComboBox->setCurrentIndex(1);

	filterPatternLineEdit->setText("*");
	filterCaseSensitivityCheckBox->setChecked(true);
	sortCaseSensitivityCheckBox->setChecked(true);
}	

void Window::setSourceModel(QAbstractItemModel *model)
{
	sourceView->setModel(model);
	proxyModel->setSourceModel(model);
}

void Window::filterRegExpChanged()
{
	QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(filterSyntaxComboBox->itemData(filterSyntaxComboBox->currentIndex()).toInt());

	Qt::CaseSensitivity caseSensitivity = filterCaseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive: Qt::CaseInsensitive;

	QRegExp regExp(filterPatternLineEdit->text(), caseSensitivity, syntax);
	proxyModel->setFilterRegExp(regExp);
}

void Window::filterColumnChanged()
{
	proxyModel->setFilterKeyColumn(filterColumnComboBox->currentIndex());
}

void Window::sortChanged()
{
	proxyModel->setSortCaseSensitivity(sortCaseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
}
