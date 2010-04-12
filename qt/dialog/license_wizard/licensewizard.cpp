#include <QtGui>
#include "licensewizard.h"

LicenseWizard:: LicenseWizard(QWidget *parent)
	: QWizard(parent)
{
	setPage(Page_Intro, new IntroPage);
	setPage(Page_Evaluate, new EvaluatePage);
	setPage(Page_Register, new RegisterPage);
	setPage(Page_Details, new DetailsPage);
	setPage(Page_Conclusion, new ConclusionPage);

	setStartId(Page_Intro);
	setOption(HaveHelpButton, true);
	setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));
	
	connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
	setWindowTitle("License Wizard");
}

void LicenseWizard::showHelp()
{
	static QString lastHelpMessage;
	
	QString message;
	
	switch (currentId())
	{
		case Page_Intro:
			message = tr("The decision you make here will affect which page you get to see next.");
			break;		
		case Page_Evaluate:
			message = tr("Make sure to provide a valid email address, such as wppan@redflag-linux.com");
			break;		
		case Page_Register:
			message = tr("If you don't provide an update key, you will be asked to fill in your details");
			break;		
		case Page_Details:
			message = tr("Make sure to provide a valid email address, such as wppan@redflag-linux.com");
			break;		
		case Page_Conclusion:
			message = tr("You must accept the terms and conditions of the license to proceed.");
			break;		
		default:
			message = tr("This help is likely not to be of any help");
	}	

	if (lastHelpMessage == message)
	{
		message = tr("Sorry, I already gave what help I could. Maybe you should try asking a human?");
	}

	QMessageBox::information(this, tr("License Wizard Help"), message);
	
	lastHelpMessage = message;
}

IntroPage::IntroPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Introduction"));

	topLabel = new QLabel(tr("This wizard will help you register your copy of"
							 "<i> Super Product One </i>&trade; or start"
							 "evaluating the product."));  	
	topLabel->setWordWrap(true);

	registerRadioButton = new QRadioButton(tr("&Register your copy"));
	evaluateRadioButton = new QRadioButton(tr("&Evaluate the product for 30 days"));
	
	registerRadioButton->setChecked(true);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	layout->addWidget(registerRadioButton);
	layout->addWidget(evaluateRadioButton);
	setLayout(layout);	
}

int IntroPage::nextId() const
{
	if (evaluateRadioButton->isChecked())
	{
		return LicenseWizard::Page_Evaluate;		
	}
	else
	{
		return LicenseWizard::Page_Register;
	}
}

EvaluatePage::EvaluatePage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Evaluate <i> Super Product One </i>&trade"));
	setSubTitle(tr("Pls fill both fields. Make sure to provide a valid email address"));
	
	nameLabel = new QLabel(tr("N&ame:"));
	nameLineEdit = new QLineEdit;
	nameLabel->setBuddy(nameLineEdit);
	
	emailLabel = new QLabel(tr("&Email address:"));
	emailLineEdit = new QLineEdit;
	emailLineEdit->setValidator(new QRegExpValidator(QRegExp(".*@*.*"), this));
	emailLabel->setBuddy(emailLineEdit);

	registerField("evaluate.name*", nameLineEdit);
	registerField("evaluate.email*", emailLineEdit);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(nameLabel, 0, 0);
	layout->addWidget(nameLineEdit, 0, 1);
	layout->addWidget(emailLabel, 1, 0);
	layout->addWidget(emailLineEdit, 1, 1);
	
	setLayout(layout);
} 

int EvaluatePage::nextId() const
{
	return LicenseWizard::Page_Conclusion;
}
	
RegisterPage::RegisterPage(QWidget *parent)
	:QWizardPage(parent)
{
	setTitle("Register Your Copy of <i> Super Product One</i>&trade;");
	setSubTitle("If you have an update key, pls fill in the appropriate field.");
	
	nameLabel = new QLabel("N&ame");
	nameLineEdit = new QLineEdit;
	nameLabel->setBuddy(nameLineEdit);

	updateKeyLabel = new QLabel("&Update key");
	updateKeyLineEdit = new QLineEdit;
	updateKeyLabel->setBuddy(updateKeyLineEdit);
	
	registerField("register.name*", nameLineEdit);
	registerField("register.updateKey", updateKeyLineEdit);	

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(nameLabel, 0, 0);
	layout->addWidget(nameLineEdit, 0, 1);
	layout->addWidget(updateKeyLabel, 1, 0);
	layout->addWidget(updateKeyLineEdit, 1, 1);
	
	setLayout(layout);
}

int RegisterPage::nextId() const
{
	if (updateKeyLineEdit->text().isEmpty())
	{
		return LicenseWizard::Page_Details;
	}
	else
	{
		return LicenseWizard::Page_Conclusion;
	}
}

DetailsPage::DetailsPage(QWidget *parent)
	:QWizardPage(parent)
{
	setTitle("Fill in your details");
	setSubTitle("Pls fill all fields, Make sure to provide a valid email address");
	
	companyLabel = new QLabel("&Company name");
	companyLineEdit = new QLineEdit;
	companyLabel->setBuddy(companyLineEdit);

	emailLabel = new QLabel("&Email address");
	emailLineEdit = new QLineEdit;
	emailLineEdit->setValidator(new QRegExpValidator(QRegExp(".*@.*"), this));
	emailLabel->setBuddy(emailLineEdit);

	postalLabel = new QLabel("&Postal address:");
	postalLineEdit = new QLineEdit;
	postalLabel->setBuddy(postalLineEdit);

	registerField("details.company*", companyLineEdit);
	registerField("details.email*", emailLineEdit);
	registerField("details.postal*", postalLineEdit);
	
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(companyLabel, 0, 0);
	layout->addWidget(companyLineEdit, 0, 1);
	layout->addWidget(emailLabel, 1, 0);
	layout->addWidget(emailLineEdit, 1, 1);
	layout->addWidget(postalLabel, 2, 0);
	layout->addWidget(postalLineEdit, 2, 1);
	
	setLayout(layout);
}

int DetailsPage::nextId() const
{
	return LicenseWizard::Page_Conclusion;
}

ConclusionPage::ConclusionPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle("Complete Your Registration");
	
	bottomLabel = new QLabel;
	bottomLabel->setWordWrap(true);
	
	agreeCheckBox = new QCheckBox("I agree to the terms of the license");
	
	registerField("conclusion.agree*", agreeCheckBox);
		
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(bottomLabel);
	layout->addWidget(agreeCheckBox);
		
	setLayout(layout);
	update();
}

void ConclusionPage::initializePage()
{
	QString licenseText;
	
	if (wizard()->hasVisitedPage(LicenseWizard::Page_Evaluate))
	{
		licenseText = tr("<u>Evaluation License Agreement:</u>"
						"You can use this software for 30 days and make one backup,"
						"but you are not allowed to distribute it.");
	}	
	else if (wizard()->hasVisitedPage(LicenseWizard::Page_Details))
	{
		licenseText = tr("<u>First-Time License Agreement:</u>"
						"You cans use this software subject to the license"
						"you will receive by email");
	}
	else
	{
		licenseText = tr("<u>Upgrade License License Agreement:</u>"
						"The software is licensed under the terms of your current license."
						);
	}
	
	bottomLabel->setText(licenseText);
}

int ConclusionPage::nextId() const
{
	return -1;
}

void ConclusionPage::setVisible(bool visible)
{
	QWizardPage::setVisible(visible);

	if (visible)
	{
		wizard()->setButtonText(QWizard::CustomButton1, tr("&Print"));
		wizard()->setOption(QWizard::HaveCustomButton1, true);
		
		connect(wizard(), SIGNAL(customButtonClicked(int)), this, SLOT(printButtonClicked()));
	}	
	else
	{
		wizard()->setOption(QWizard::HaveCustomButton1, false);
		disconnect(wizard(), SIGNAL(customButtonClicked(int)), this, SLOT(printButtonClicked()));
	}
}
	
void ConclusionPage::printButtonClicked()
{
	QPrinter printer;
	QPrintDialog dialog(&printer, this);
	
	if (dialog.exec())
	{
		QMessageBox::warning(this, tr("Print license"),
							tr("As an environmentally friendly measure, the license text will not actually be printed"));
	}	
}
	
