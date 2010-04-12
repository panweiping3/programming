#include "configdialog.h"
#include "pages.h"

#include <QtGui>
#include <QMessageBox>

ConfigDialog::ConfigDialog()
{
	contentsWidget = new QListWidget;
	contentsWidget->setViewMode(QListView::IconMode);
	contentsWidget->setIconSize(QSize(96, 84));
	contentsWidget->setMovement(QListView::Static);
	contentsWidget->setMaximumWidth(128);
	contentsWidget->setSpacing(12);
	
	pagesWidget = new QStackedWidget;
	pagesWidget->addWidget(new ConfigurationPage);
	pagesWidget->addWidget(new UpdatePage);
	pagesWidget->addWidget(new QueryPage);
	
	QPushButton *closeButton = new QPushButton("Close");
	
	createIcons();
	contentsWidget->setCurrentRow(0);

	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	
	QHBoxLayout *horizontalLayout = new QHBoxLayout;
	horizontalLayout->addWidget(contentsWidget);
	horizontalLayout->addWidget(pagesWidget, 1);
	
	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch(1);
	buttonsLayout->addWidget(closeButton);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(horizontalLayout);	
	mainLayout->addStretch(1);
	mainLayout->addSpacing(12);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);
	
	setWindowTitle("Config Dialog");
}

void ConfigDialog::itemDoubleClicked(QListWidgetItem *item)
{
	QMessageBox::warning(this, tr("Item clicked"), item->text(), QMessageBox::Ok);
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (current == NULL)
	{
		current = previous;
	}

	pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void ConfigDialog::createIcons()
{
	QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);	
	configButton->setIcon(QIcon(":/images/config.png"));
	configButton->setText("Configuration");
	configButton->setTextAlignment(Qt::AlignHCenter);
	configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	
	QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);	
	updateButton->setIcon(QIcon(":/images/update.png"));
	updateButton->setText("Update");
	updateButton->setTextAlignment(Qt::AlignHCenter);
	updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	
	QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
	queryButton->setIcon(QIcon(":/images/query.png"));
	queryButton->setText("Query");
	queryButton->setTextAlignment(Qt::AlignHCenter);
	queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(changePage(QListWidgetItem *, QListWidgetItem *)));

	connect(contentsWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemDoubleClicked(QListWidgetItem *)));
}

