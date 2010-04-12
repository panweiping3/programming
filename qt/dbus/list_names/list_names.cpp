#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtDBus/QtDBus>
void method1();
void method2();
void method3();
void method4();

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (!QDBusConnection::systemBus().isConnected()) {
        fprintf(stderr, "Cann't connect to the D-Bus system bus.\n"
                        "To start it, run:\n"
                        "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cann't connect to the D-Bus session bus.\n"
                        "To start it, run:\n"
                        "\teval `dbus-launch --auto-syntax`\n");
        return 2;
    }

    method1();
    method2();
    method3();
    method4();

    return 0;
}

void method1()
{
    qDebug() << "-----------------------------------------------------";
    qDebug() << __func__ << __LINE__;

    QDBusReply<QStringList> reply = QDBusConnection::sessionBus().interface()->registeredServiceNames();
    if (!reply.isValid()) {
        qDebug() << "Error:" << reply.error().message();
        exit(1);
    }

    foreach (QString name, reply.value()) {
        qDebug() << name;
    }
    qDebug() << "-----------------------------------------------------";
}

void method2()
{
    qDebug() << "-----------------------------------------------------";
    qDebug() << __func__ << __LINE__;
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface dbus_interface("org.freedesktop.DBus", "/org/freedesktop/DBus",                                  "org.freedesktop.DBus", bus);
    //qDebug() << dbus_interface.call("ListNames").arguments().at(0);
    qDebug() << dbus_interface.call("ListNames");
    qDebug() << "-----------------------------------------------------";
}

void method3()
{
    qDebug() << "-----------------------------------------------------";
    qDebug() << __func__ << __LINE__;
    qDebug() << QDBusConnection::sessionBus().interface()->registeredServiceNames().value();
    qDebug() << "-----------------------------------------------------";
}

void method4()
{
    qDebug() << "-----------------------------------------------------";
    qDebug() << __func__ << __LINE__;
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusInterface dbus_interface("net.reactivated.Fprint", "/net/Fprint/Manager", "net.reactivated.Fprint", bus);
    qDebug() << dbus_interface.call("GetDevices");
    qDebug() << "-----------------------------------------------------";
}
