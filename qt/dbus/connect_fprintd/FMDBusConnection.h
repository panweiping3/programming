#ifndef FMDBUSCONNECTION_H
#define FMDBUSCONNECTION_H

#include <QtCore/QStringList>
#include <QtDBus/QtDBus>

#define GET_MANAGER_INTERFACE_RETRY 30
class FMDBusConnection : QObject
{
    public:
        FMDBusConnection();
        ~FMDBusConnection();
    
        QDBusInterface *getManagerInterface();
        QDBusInterface *getDeviceInterface(const QString &devicePath);
        QDBusInterface *getDevicePropertyInterface(const QString &devicePath);
        bool getAllDevices();
        QStringList getAllDevicesPaths();
        QStringList getAllDevicesNames();
        QString getDefaultDevicePath();
        QString getDefaultDeviceName();
        QString getDeviceName(const QString &devicePath);
        QString getScanType(const QString &devicePath);
        int getEnrollStages(const QString &devicePath);
        QStringList getEnrolledFingers(const QString &devicePath, const QString &userName);

    public:
        void EnrollStatusSlot(const QString& result, bool done);

    private:

        // QMap <devicePath, deviceName> devicesMap;
        QMap<QString, QString> m_devicesMap;
};
#endif
