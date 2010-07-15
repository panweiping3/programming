#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

static const char *table_students = "CREATE TABLE students ("
    "ID INTEGER PRIMARY KEY,"
    "name VARCHAR(255)"
    ")";

const QString DATABASE_NAME = "pwp.db";
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(DATABASE_NAME);
	if (!db.open()) {
		qDebug() <<__FILE__ << __LINE__ << __func__ << "open db error";
		return -1;
	}

	if (db.tables().count() == 0) {
		QSqlQuery query = QSqlQuery(db);
		query.exec(table_students);
		qDebug() << "create tabel students!";
	}
	
	db.close();
	qDebug() << "u can use Ctrl + C to make me quit!";
	return app.exec();
} 
