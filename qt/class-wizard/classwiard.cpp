#include <QtGui>

#include "classwizard.h"

ClassWizard::ClassWizard(QWidget *parent)
	: QWidget(parent)
{
	addPage(new IntroPage);
	addPage(new ClassInfoPage);
	addPage(new CodeStylePage);
	addPage(new OutputFilesPage);
	addPage(new ConclusionPage);

	setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));

	setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));
	
	setWindowTitle("Class Wizard");
}

void ClassWizard::accept()
{
	QByteArray className = field("className").toByteArray();
	QByteArray baseClass = field("baseClass").toByteArray();
	QByteArray macroName = field("macroName").toByteArray();
	QByteArray baseInclude = field("baseInclude").toByteArray();	

	QString outputDir = field("outputDir").toString();
	QString header = field("header").toString();
	QString implementation = field("implementation").toString();

	QByteArray block;
	
	if (field("comment").toBool() == true)
	{
		block += "/*\n";
		block += "		" + header.toAscii() + "\n";
		block += "*/\n";
		block += "\n";
	}

	if (field("protect").toBool() == true)
	{
		block += "#ifndef " + macroName + "\n";
		block += "#define " + macroName + "\n";
		block += "\n"; 
	}	

	if (field("includeBase").toBool() == true)
	{
		block += "#include " + baseInclude + "\n";
		block += "\n";
	}
	
	block += "class " + className;
	
	if (baseClass.isEmpty() == false)
	{
		block += " : public " + baseClass;	
	}

	block += "\n";
	block += "{\n";
}
