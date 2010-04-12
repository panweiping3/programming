#include "../ping-common.h"
#include "pong.h"

#include <stdio.h>
#include <stdlib.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtDBus/QtDBus>

QString Pong::ping(const QString &arg)
{
    //QMetaObject::invokeMethod(QCoreApplication::instance(), "quit");
    return QString("ping(\"%1\") got called").arg(arg);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cann't connect to the D-Bus session bus.\n"
                        "To start it, run:\n"
                        "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }
    
    Pong pong;
    QDBusConnection::sessionBus().registerObject("/", &pong, QDBusConnection::ExportAllSlots);

    app.exec();
    return 0;
}
