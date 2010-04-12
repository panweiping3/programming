#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSplitter *splitter = new QSplitter;

	QDirModel *model = new QDirModel;

	QTreeView *tree = new QTreeView(splitter);
	tree->setModel(model);
	tree->setRootIndex(model->index(QDir::homePath()));

	QTableView *table = new QTableView(splitter);
	table->setModel(model);
	table->setRootIndex(model->index(QDir::homePath()));

	splitter->setWindowTitle("Two views onto the same directory");
	splitter->show();
	
	return app.exec();
}
