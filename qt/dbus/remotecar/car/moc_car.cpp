/****************************************************************************
** Meta object code from reading C++ file 'car.h'
**
** Created: Fri Sep 4 05:00:01 2009
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "car.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'car.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Car[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      15,    4,    4,    4, 0x0a,
      28,    4,    4,    4, 0x0a,
      41,    4,    4,    4, 0x0a,
      52,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Car[] = {
    "Car\0\0crashed()\0accelerate()\0decelerate()\0"
    "turnLeft()\0turnRight()\0"
};

const QMetaObject Car::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Car,
      qt_meta_data_Car, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Car::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Car::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Car::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Car))
        return static_cast<void*>(const_cast< Car*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Car*>(this));
    return QObject::qt_metacast(_clname);
}

int Car::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: crashed(); break;
        case 1: accelerate(); break;
        case 2: decelerate(); break;
        case 3: turnLeft(); break;
        case 4: turnRight(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Car::crashed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
