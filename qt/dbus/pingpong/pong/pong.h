#ifndef PONG_H
#define PONG_H

#include <QtCore/QObject>

class Pong : public QObject
{
    Q_OBJECT

    public slots:
        Q_SCRIPTABLE QString ping(const QString &arg);
};
#endif
