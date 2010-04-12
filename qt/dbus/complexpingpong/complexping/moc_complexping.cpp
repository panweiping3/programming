/****************************************************************************
** Meta object code from reading C++ file 'complexping.h'
**
** Created: Tue Sep 1 04:44:17 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "complexping.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'complexping.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Ping[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    6,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Ping[] = {
    "Ping\0\0,,\0start(QString,QString,QString)\0"
};

const QMetaObject Ping::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Ping,
      qt_meta_data_Ping, 0 }
};

const QMetaObject *Ping::metaObject() const
{
    return &staticMetaObject;
}

void *Ping::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ping))
        return static_cast<void*>(const_cast< Ping*>(this));
    return QObject::qt_metacast(_clname);
}

int Ping::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
