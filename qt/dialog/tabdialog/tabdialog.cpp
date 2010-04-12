#include "tabdialog.h"

#include <QtGui>

TabDialog::TabDialog(const QString &fileName, QWidget *parent)
	: QDialog(parent)
{
	QFileInfo fileInfo(fileName);
	
	tabWidget = new QTabWidget;
//	tabWidget->setTabShape(QTabWidget::Triangular);
	tabWidget->addTab(new GeneralTab(fileInfo), QIcon(":/images/goto.png"), "General");
	tabWidget->setTabToolTip(0, "General information");
	tabWidget->addTab(new PermissionTab(fileInfo), QIcon(":/images/ok.png"), "Permissions");
	tabWidget->setTabToolTip(1, "Permissions information");
	tabWidget->addTab(new ApplicationTab(fileInfo), QIcon(":/images/add.png"), "Applications");
	tabWidget->setTabToolTip(2, "Applications information");

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);
	mainLayout->addWidget(buttonBox);
	
	setLayout(mainLayout);
	setWindowTitle("Tab Dialog");
}	
GeneralTab::GeneralTab(const QFileInfo &fileInfo, QWidget *parent)
	: QWidget(parent)
{
	QLabel *fileNameLabel = new QLabel("File Name:");
	QLineEdit *fileNameEdit = new QLineEdit(fileInfo.fileName());
	
	QLabel *pathLabel = new QLabel("Path:");
	QLabel *pathValueLabel = new QLabel(fileInfo.absoluteFilePath());
	pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

	QLabel *sizeLabel = new QLabel("Size:");
	qlonglong size = fileInfo.size() / 1024;
	QLabel *sizeValueLabel = new QLabel(QString("%1 K").arg(size));
	sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	
	QLabel *lastReadLabel = new QLabel("Last read:");
	QLabel *lastReadValueLabel = new QLabel(fileInfo.lastRead().toString());
	lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

	QLabel *lastModifiedLabel = new QLabel("Last modified:");
	QLabel *lastModifiedValueLabel = new QLabel(fileInfo.lastModified().toString());
	lastModifiedValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(fileNameLabel);
	mainLayout->addWidget(fileNameEdit);
	mainLayout->addWidget(pathLabel);
	mainLayout->addWidget(pathValueLabel);
	mainLayout->addWidget(sizeLabel);
	mainLayout->addWidget(sizeValueLabel);
	mainLayout->addWidget(lastReadLabel);
	mainLayout->addWidget(lastReadValueLabel);
	mainLayout->addWidget(lastModifiedLabel);
	mainLayout->addWidget(lastModifiedValueLabel);
	mainLayout->addStretch(1);
	
	setLayout(mainLayout);
}

PermissionTab::PermissionTab(const QFileInfo &fileInfo, QWidget *parent)
	: QWidget(parent)
{
	QGroupBox *permissionGroup = new QGroupBox("Permissions");
	
	QCheckBox *readable = new QCheckBox("Readable");
	
	if (fileInfo.isReadable() == true)
	{
		readable->setChecked(true);
	}
	
	QCheckBox *writeable = new QCheckBox("Writable");
	
	if (fileInfo.isWritable() == true)
	{
		writeable->setChecked(true);
	}

	QCheckBox *executable = new QCheckBox("Executable");
	
	if (fileInfo.isExecutable() == true)
	{
		executable->setChecked(true);
	}

	QGroupBox *ownerGroup = new QGroupBox("Ownership");	
	
	QLabel *ownerLabel = new QLabel("Owner");
	QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
	ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

	QLabel *groupLabel = new QLabel("Group");
	QLabel *groupValueLabel = new QLabel(fileInfo.group());
	groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

	QVBoxLayout *permissionsLayout = new QVBoxLayout;
	permissionsLayout->addWidget(readable);
	permissionsLayout->addWidget(writeable);
	permissionsLayout->addWidget(executable);
	permissionGroup->setLayout(permissionsLayout);

	QVBoxLayout *ownerLayout = new QVBoxLayout;
	ownerLayout->addWidget(ownerLabel);
	ownerLayout->addWidget(ownerValueLabel);
	ownerLayout->addWidget(groupLabel);
	ownerLayout->addWidget(groupValueLabel);
	ownerGroup->setLayout(ownerLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(permissionGroup);	
	mainLayout->addWidget(ownerGroup);
	mainLayout->addStretch(1);
	
	setLayout(mainLayout);	
}

ApplicationTab::ApplicationTab(const QFileInfo &fileInfo, QWidget *parent)
	: QWidget(parent)
{
	QLabel *topLabel = new QLabel("Open with:");
	
	QListWidget *applicationsListBox = new QListWidget;
	QStringList applications;
	
	for (int i=0; i<=30; ++i)
	{
		applications.append(QString("Application %1").arg(i));
	}

	applicationsListBox->insertItems(0, applications);
	
	QCheckBox *alwaysCheckBox;
	
	if (fileInfo.suffix().isEmpty() == true)
	{
		alwaysCheckBox = new QCheckBox("Always use this application to open this type of file");
	}
	else
	{
		alwaysCheckBox = new QCheckBox(QString("Always use this application to open files with the extension %1").arg(fileInfo.suffix()));
	}

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	layout->addWidget(applicationsListBox);
	layout->addWidget(alwaysCheckBox);
	
	setLayout(layout);
}


