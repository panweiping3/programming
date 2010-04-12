#include "../ping-common.h"
#include "complexpong.h"

#include <stdio.h>
#include <stdlib.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtDBus/QtDBus>

QString Pong::value() const
{
    return m_value;
}

void Pong::setValue(const QString &newValue)
{
    m_value = newValue;
}

void Pong::quit()
{
    QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));
}

QDBusVariant Pong::query(const QString &query)
{
    QString q = query.toLower();

    if (q == "hello") {
        return QDBusVariant("world");
    }

    if (q == "ping") {
        return QDBusVariant("pong");
    }

    if (q.indexOf("the answer to life, the universe and everything") != -1) {
        return QDBusVariant(42);
    }

    if (q.indexOf("unladen swallow") != -1) {
        if (q.indexOf("european") != -1) {
            return QDBusVariant(11.0);
        }

        return QDBusVariant(QByteArray("african or european"));
    }

    return QDBusVariant("Sorry, I don't know the answer");
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QObject obj;
    Pong *pong = new Pong(&obj);
    pong->connect(&app, SIGNAL(aboutToQuit()), SIGNAL(aboutToQuit()));
    pong->setProperty("value", "initial value");

    QDBusConnection::sessionBus().registerObject("/", &obj);

    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    app.exec();
    return 0;
}
