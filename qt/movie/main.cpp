#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QMovie>

int main(int argc, char *argv[])
{
		QApplication app(argc, argv);
		QDialog dia;
		dia.setFixedSize(800, 600);	
		QLabel *label = new QLabel("haha", &dia);
		QMovie *movie = new QMovie("throbber.gif");

		label->setMovie(movie);
		movie->start();	
		dia.show();
		return app.exec();
}
