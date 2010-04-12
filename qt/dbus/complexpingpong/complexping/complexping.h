#ifndef COMPLEXPING_H
#define COMPLEXPING_H

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtDBus/QDBusInterface>

class Ping : public QObject
{
    Q_OBJECT

    public slots:
        void start(const QString &, const QString &, const QString &);

    public:
        QFile qstdin;
        QDBusInterface *iface;
};

#endif
