#include <QtGui>

#include "pages.h" 

ConfigurationPage::ConfigurationPage(QWidget *parent)
	: QWidget(parent)
{
	QGroupBox *configGroup = new QGroupBox("Server configuration");
	
	QLabel *serverLabel = new QLabel("Server:");
	QComboBox *serverComboBox = new QComboBox;
	serverComboBox->addItem("Qt software (Australia)");	
	serverComboBox->addItem("Qt software (Germany)");	
	serverComboBox->addItem("Qt software (Normay)");	
	serverComboBox->addItem("Qt software (China)");	
	serverComboBox->addItem("Qt software (USA)");	

	QHBoxLayout *serverLayout = new QHBoxLayout;
	serverLayout->addWidget(serverLabel);
	serverLayout->addWidget(serverComboBox);

	QVBoxLayout *configLayout = new QVBoxLayout;
	configLayout->addLayout(serverLayout);
	configGroup->setLayout(configLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(configGroup);	
	mainLayout->addStretch(1);

	setLayout(mainLayout);
}

QueryPage:: QueryPage(QWidget *parent)
	: QWidget(parent)
{
	QGroupBox *packagesGroup = new QGroupBox("Look for packages");
	
	QLabel *nameLabel = new QLabel("Name:");
	QLineEdit *nameLineEdit = new QLineEdit;
	
	QLabel *dateLabel = new QLabel("Released after:");
	QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());
	
	QCheckBox *releaseCheckBox = new QCheckBox("Releases");
	QCheckBox *upgradesCheckBox = new QCheckBox("Upgrades");
	
	QSpinBox *hitsSpinBox = new QSpinBox;
	hitsSpinBox->setPrefix("Return up to");	
	hitsSpinBox->setSuffix(" results");
	hitsSpinBox->setSpecialValueText("Return only the first result");
	hitsSpinBox->setMinimum(1);
	hitsSpinBox->setMaximum(100);
	hitsSpinBox->setSingleStep(10);
	
	QPushButton *startQueryButton = new QPushButton("Start query");
	
	QGridLayout *packagesLayout = new QGridLayout;
	packagesLayout->addWidget(nameLabel, 0, 0);
	packagesLayout->addWidget(nameLineEdit, 0, 1);
	packagesLayout->addWidget(dateLabel, 1, 0);
	packagesLayout->addWidget(dateEdit, 1, 1);
	packagesLayout->addWidget(releaseCheckBox, 2, 0);
	packagesLayout->addWidget(upgradesCheckBox, 3, 0);
	packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
	packagesGroup->setLayout(packagesLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(packagesGroup);
	mainLayout->addSpacing(12);
	mainLayout->addWidget(startQueryButton);
	mainLayout->addStretch(1);
	
	setLayout(mainLayout);
}

UpdatePage:: UpdatePage(QWidget *parent)	
	: QWidget(parent)
{
	QGroupBox *updateGroup = new QGroupBox("Package seletion");
	QCheckBox *systemCheckBox = new QCheckBox("Update system");
	QCheckBox *appsCheckBox = new QCheckBox("Update applications");
	QCheckBox *docsCheckBox = new QCheckBox("Update documentation");
	
	QGroupBox *packageGroup = new QGroupBox("Existing packages");
	
	QListWidget *packageList = new QListWidget;
	QListWidgetItem *qtItem = new QListWidgetItem(packageList);
	qtItem->setText(tr("Qt"));
	
	QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
	qsaItem->setText(tr("QSA"));
	
	QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
	teamBuilderItem->setText(tr("TeamBuilder"));
	
	QPushButton *startUpdateButton = new QPushButton("Start update");	
		
	QVBoxLayout *updateLayout = new QVBoxLayout;
	updateLayout->addWidget(systemCheckBox);
	updateLayout->addWidget(appsCheckBox);
	updateLayout->addWidget(docsCheckBox);
	updateGroup->setLayout(updateLayout);

	QVBoxLayout *packageLayout = new QVBoxLayout;
	packageLayout->addWidget(packageList);
	packageGroup->setLayout(packageLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(updateGroup);
	mainLayout->addWidget(packageGroup);
	mainLayout->addSpacing(12);
	mainLayout->addWidget(startUpdateButton);
	mainLayout->addStretch(1);
	setLayout(mainLayout);
}

