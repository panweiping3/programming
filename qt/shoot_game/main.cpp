#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include "gameboard.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QString locale = QLocale::system().name();

    QTranslator translator;
    translator.load(QString("shoot_game_cn.ts") + locale);
    app.installTranslator(&translator);	
	
	GameBoard board;	
	board.setGeometry(100, 100, 500, 355);
	board.show();
	return app.exec();
}

