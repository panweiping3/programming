#include "wizard.h"

GuideWizard::GuideWizard()
{
 	QWizardPage *page0 = new QWizardPage;
    page0->setTitle(tr("Welcome"));
	
 	QWizardPage *page1 = new QWizardPage;
    page1->setTitle(tr("DOO"));

 	QWizardPage *page2 = new QWizardPage;
    page2->setTitle(tr("Finish"));

	addPage(page0);
	addPage(page1);
	addPage(page2);
}


