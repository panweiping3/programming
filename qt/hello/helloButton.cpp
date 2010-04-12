#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    int n = 3;

	QPushButton *button = new QPushButton(QObject::tr("%n message(s)", "", n));
	QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
	button->show();

	return app.exec();
}
