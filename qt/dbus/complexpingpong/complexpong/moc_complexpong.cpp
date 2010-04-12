/****************************************************************************
** Meta object code from reading C++ file 'complexpong.h'
**
** Created: Tue Sep 1 04:47:51 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "complexpong.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'complexpong.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Pong[] = {

 // content:
       2,       // revision
       0,       // classname
       1,   12, // classinfo
       3,   14, // methods
       1,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // classinfo: key, value
      41,    5,

 // signals: signature, parameters, type, tag, flags
      58,   57,   57,   57, 0x05,

 // slots: signature, parameters, type, tag, flags
      91,   85,   72,   57, 0x0a,
     116,   57,   57,  106, 0x0a,

 // properties: name, type, flags
     131,  123, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_Pong[] = {
    "Pong\0com.redflag.QtDBus.ComplexPong.Pong\0"
    "D-Bus Interface\0\0aboutToQuit()\0"
    "QDBusVariant\0query\0query(QString)\0"
    "Q_NOREPLY\0quit()\0QString\0value\0"
};

const QMetaObject Pong::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_Pong,
      qt_meta_data_Pong, 0 }
};

const QMetaObject *Pong::metaObject() const
{
    return &staticMetaObject;
}

void *Pong::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Pong))
        return static_cast<void*>(const_cast< Pong*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int Pong::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: aboutToQuit(); break;
        case 1: { QDBusVariant _r = query((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusVariant*>(_a[0]) = _r; }  break;
        case 2: quit(); break;
        default: ;
        }
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = value(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setValue(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Pong::aboutToQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
