#include "FMDBusConnection.h"

#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (!QDBusConnection::systemBus().isConnected()) {
        fprintf(stderr, "Cann't connect to the D-Bus system bus.\n"
                        "To start it, run:\n"
                        "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    FMDBusConnection fmDBusConnection;
    fmDBusConnection.getAllDevices();
    qDebug() << __FILE__ << __LINE__ << __func__ << "getAllDevicesPaths" << fmDBusConnection.getAllDevicesPaths();
    qDebug() << __FILE__ << __LINE__ << __func__ << "getAllDevicesNames" << fmDBusConnection.getAllDevicesNames();
    QString defaultDevicePath = fmDBusConnection.getDefaultDevicePath();
    qDebug() << __FILE__ << __LINE__ << __func__ << "getDefaultDeviceName" << fmDBusConnection.getDefaultDeviceName();

    qDebug() << __LINE__ << fmDBusConnection.getScanType(defaultDevicePath);
    qDebug() << __LINE__ << fmDBusConnection.getEnrolledFingers(defaultDevicePath, "pwp");
    qDebug() << __LINE__ << fmDBusConnection.getEnrollStages(defaultDevicePath);
    return 0;
}

