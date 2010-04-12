#include "FMDBusConnection.h"

#include <QDebug>

FMDBusConnection::FMDBusConnection() 
{
    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug() << "Cann't connect to the D-Bus system bus.";
        qDebug() << "To start it, run:";
        qDebug() << "eval `dbus-launch --auto-syntax`";
    }
}

FMDBusConnection::~FMDBusConnection() 
{
    m_devicesMap.clear();
}
    
QDBusInterface *FMDBusConnection::getManagerInterface()
{
    QDBusConnection systemBus = QDBusConnection::systemBus();

    for (int i = 0; i < GET_MANAGER_INTERFACE_RETRY; ++i) {
    	QDBusInterface *manager_interface = new QDBusInterface( "net.reactivated.Fprint", 
                                                            "/net/reactivated/Fprint/Manager", 
                                                            "net.reactivated.Fprint.Manager", 
                                                            systemBus, 
                                                            this);
        if (manager_interface->isValid()) {
            qDebug() << "I've connected to net.reactivated.Fprint";
            return manager_interface;
        }

        sleep(1);
    }

    return NULL;
}

QDBusInterface *FMDBusConnection::getDeviceInterface(const QString &devicePath)
{
    QDBusInterface *deviceInterface = new QDBusInterface(  "net.reactivated.Fprint",
                                                            devicePath,
                                                            "net.reactivated.Fprint.Device",
                                                            QDBusConnection::systemBus()
                                                         ); 
    return deviceInterface;
}

QDBusInterface *FMDBusConnection::getDevicePropertyInterface(const QString &devicePath)
{
	QDBusInterface *devicePropertyInterface = new QDBusInterface("net.reactivated.Fprint",
                               			   devicePath, 
                                		   "org.freedesktop.DBus.Properties",
                                		   QDBusConnection::systemBus());
	if (devicePropertyInterface->isValid()) {
		return devicePropertyInterface;
	} else {
		return NULL;
	}
}

bool FMDBusConnection::getAllDevices()
{
    m_devicesMap.clear();
    QDBusInterface *manager_interface = getManagerInterface();
    if (manager_interface && manager_interface->isValid()) {
        QDBusReply<QList<QDBusObjectPath> > devicesPathsReply = manager_interface->call("GetDevices");
        if (devicesPathsReply.isValid()) {
            for (int i = 0; i < devicesPathsReply.value().count(); ++i) {
                QDBusObjectPath devicePath = devicesPathsReply.value().at(i);
                m_devicesMap.insert(devicePath.path(), getDeviceName(devicePath.path()));
            }

            return true;
        }
    }

    return false;
}

QStringList FMDBusConnection::getAllDevicesPaths()
{
    QStringList devicesPaths;
    QMap<QString, QString>::const_iterator it;
    for (it = m_devicesMap.begin(); it != m_devicesMap.end(); ++it) {
        devicesPaths << it.key();
    }

    return devicesPaths;
}

QStringList FMDBusConnection::getAllDevicesNames()
{
    QStringList devicesNames;
    QMap<QString, QString>::const_iterator it;
    for (it = m_devicesMap.begin(); it != m_devicesMap.end(); ++it) {
        devicesNames << it.value();
    }

    return devicesNames;
}

QString FMDBusConnection::getDefaultDevicePath()
{
    QString defaultDevicePath;
    QDBusInterface *manager_interface = getManagerInterface();
    if (manager_interface && manager_interface->isValid()) {
        QDBusReply<QDBusObjectPath> devicePathReply = manager_interface->call("GetDefaultDevice");
        if (devicePathReply.isValid()) {
            defaultDevicePath = devicePathReply.value().path();
        }
    }

    return defaultDevicePath;
}

QString FMDBusConnection::getDefaultDeviceName()
{
    QString defaultDevicePath = getDefaultDevicePath();
    return getDeviceName(defaultDevicePath);
}

QStringList FMDBusConnection::getEnrolledFingers(const QString &devicePath, const QString &userName)
{
    QDBusInterface *deviceInterface = getDeviceInterface(devicePath);
    if (deviceInterface->isValid()) {
        QDBusReply<QStringList> enrolledFingersReply = deviceInterface->call("ListEnrolledFingers", userName);
        if (enrolledFingersReply.isValid()) {
            delete deviceInterface;
            return enrolledFingersReply.value();
        }
    }

    delete deviceInterface;
    return QStringList(); 
}

// Get device properties
QString FMDBusConnection::getDeviceName(const QString &devicePath)
{
    QString deviceName;
    QDBusInterface *deviceInterface = getDeviceInterface(devicePath);
    if (deviceInterface->isValid()) {
        deviceName = deviceInterface->property("name").toString();
    }

    delete deviceInterface;
    
    return deviceName;
}

QString FMDBusConnection::getScanType(const QString &devicePath)
{
    QString scanType = "swipe";
    QDBusInterface *devicePropertyInterface = getDevicePropertyInterface(devicePath);
    if (devicePropertyInterface->isValid()) {
	QDBusReply<QVariant> scanTypeReply = devicePropertyInterface->call("Get",
                                        		"net.reactivated.Fprint.Device",
                                        		"scan-type");
        scanType = scanTypeReply.value().toString();
    }

    delete devicePropertyInterface;
    return scanType;
}

int FMDBusConnection::getEnrollStages(const QString &devicePath)
{
    int enrollStages = -1;
    QDBusInterface *devicePropertyInterface = getDevicePropertyInterface(devicePath);
    if (devicePropertyInterface->isValid()) {
	QDBusReply<QVariant> enrollStagesReply = devicePropertyInterface->call("Get",
                                        		"net.reactivated.Fprint.Device",
                                        		"num-enroll-stages");
        enrollStages = enrollStagesReply.value().toInt();
    }

    delete devicePropertyInterface;
    return enrollStages;
}

/*
* enroll-completed:  The enrollment successfully completed, Device.EnrollStop should now be called.
* enroll-failed: The enrollment failed, Device.EnrollStop should now be called.
* enroll-stage-passed: One stage of the enrollment passed, the enrollment is still ongoing.
* enroll-retry-scan: The user should retry scanning their finger, the enrollment is still ongoing.
* enroll-swipe-too-short: The user's swipe was too short. The user should retry scanning their finger, the enrollment is still ongoing.
* enroll-finger-not-centered: The user's finger was not centered on the reader. The user should retry scanning their finger, the enrollment is still ongoing.
* enroll-remove-and-retry: The user should remove their finger from the reader and retry scanning their finger, the enrollment is still ongoing.
* enroll-unknown-error: An unknown error occurred (usually a driver problem), Device.EnrollStop should now be called.
*/
void FMDBusConnection::EnrollStatusSlot(const QString& result, bool done)
{
    if (result == "enroll-completed") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "enroll completed";
    };

    if (result == "enroll-failed") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "enroll failed";
    };
    if (result == "enroll-stage-passed") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "one stage passed, go on";
    };
    if (result == "enroll-retry-scan") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "retry scan";
    };
    if (result == "enroll-finger-not-centered") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "finger not centered";
    };
    if (result == "enroll-remove-and-retry") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "remove-and-retry";
    };
    if (result == "enroll-unknown-error") {
        qDebug() << __FILE__ << __LINE__ << __func__ << "unknown error";
    };
}
