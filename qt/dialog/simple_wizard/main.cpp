#include <QtGui>

QWizardPage *createIntropage()
{
	QWizardPage *page = new QWizardPage;
	page->setTitle("Introduction"); 
	
	QLabel *label = new QLabel("This wizard will help you");
	label->setWordWrap(true);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	page->setLayout(layout);

	return page;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QString translatorFileName = QLatin1String("qt_");
	translatorFileName += QLocale::system().name();
	QTranslator *translator = new QTranslator(&app);
	
	if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
	{
		app.installTranslator(translator);
	}
	
	QWizard wizard;
	wizard.addPage(createIntropage());
	
	wizard.setWindowTitle("Trival wizard");
	wizard.show();
	
	return app.exec();
}
