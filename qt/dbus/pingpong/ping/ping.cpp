#include "../ping-common.h"

#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cann't connect to the D-Bus session bus.\n"
                        "To start it, run:\n"
                        "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    QDBusInterface iface(SERVICE_NAME, "/", "", QDBusConnection::sessionBus());
    if (iface.isValid()) {
        QDBusReply<QString>  reply = iface.call("ping", argc > 1 ? QString(argv[1]) : QString(""));

        if (reply.isValid()) {
            printf("Reply was :%s\n", qPrintable(reply.value()));
            return 0;
        }

        fprintf(stderr, "Call failed:%s\n", qPrintable(reply.error().message()));
        return 1;
    }

    fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));

    return 1;
}
