#include "window.h"
#include "colorlisteditor.h"
#include <QtGui>

Window::Window()
{
	QItemEditorFactory *factory = new QItemEditorFactory;

	QItemEditorCreatorBase *colorListCreator  = new QStandardItemEditorCreator<ColorListEditor>();
	factory->registerEditor(QVariant::Color, colorListCreator);
	
	QItemEditorFactory::setDefaultFactory(factory);

	createGUI();
}

void Window::createGUI()
{
	QList <QPair<QString, QColor> > list;
	list<< QPair<QString, QColor>("Alice", QColor("aliceblue"))
		<< QPair<QString, QColor>("Neptun", QColor("aquamarine"))
		<< QPair<QString, QColor>("Ferdinand", QColor("springgreen"));
	
	QTableWidget *table = new QTableWidget(3, 2);
	table->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Hair Color"));
	
	table->verticalHeader()->setVisible(false);
	table->resize(400, 300);
	
	for (int i = 0; i < 3; ++i)
	{
		QPair <QString, QColor> pair = list.at(i);
		
		QTableWidgetItem *nameItem = new QTableWidgetItem(pair.first);
		QTableWidgetItem *colorItem = new QTableWidgetItem;
		colorItem->setData(Qt::DisplayRole, pair.second);
	
		table->setItem(i, 0, nameItem);
		table->setItem(i, 1, colorItem);
	}

	table->resizeColumnToContents(0);
	table->horizontalHeader()->resizeSection(1, 150);
	
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(table, 0, 0);	

	setLayout(layout);
	
	setWindowTitle("Color Editor Factory");
}
