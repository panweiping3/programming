#include <QApplication>
#include <QtGui>
#include <QHeaderView>

#include "stringlistmodel.h"
#include "spinboxdelegate.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    QStringList strings;
    strings << "a";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";
    strings << "b";

    QAbstractItemModel *model = new StringListModel(strings);

    QHeaderView *header = new QHeaderView(Qt::Vertical);
    header->setModel(model);

    QAbstractItemDelegate *delegate = new SpinBoxDelegate();

	QTableView *table = new QTableView();
	table->setModel(model);
    table->setItemDelegate(delegate);
    table->setVerticalHeader(header);
    table->show();

	return app.exec();
}
