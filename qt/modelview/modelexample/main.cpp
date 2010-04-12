#include "stringlistmodel.h"

#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget *widget = new QWidget;

	QStringList list;
	list << "pwp" << "xuli";

	QAbstractItemModel *model = new StringListModel(list);
	model->insertRows(0, 1, QModelIndex());
	model->setData(model->index(0, 0), QString("haha"), Qt::EditRole);

	QTreeView *tree = new QTreeView(widget);
	tree->setModel(model);

	QListView *listView = new QListView(widget);
	listView->setModel(model);
	listView->setSelectionModel(tree->selectionModel());

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(tree);
	layout->addWidget(listView);
	
	widget->setLayout(layout);

	widget->setWindowTitle("Two views onto the same directory");
	widget->resize(400, 300);
	widget->show();
	
	return app.exec();
}
