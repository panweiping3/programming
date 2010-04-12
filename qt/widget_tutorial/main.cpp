#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QWidget *window = new QWidget();
	window->resize(800, 600);
	
	QLabel *label = new QLabel("query:");
	label->resize(50, 30);

	QLineEdit *lineEdit = new QLineEdit();
	lineEdit->setFixedSize(100, 30);
	
	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(label);
	hLayout->addWidget(lineEdit);


	QTableView *resultView = new QTableView();

	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->addLayout(hLayout);
	vLayout->addWidget(resultView);

	window->setLayout(vLayout);
	window->show();
	return app.exec();
}
