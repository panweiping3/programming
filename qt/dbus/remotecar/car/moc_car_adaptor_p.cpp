/****************************************************************************
** Meta object code from reading C++ file 'car_adaptor_p.h'
**
** Created: Fri Sep 4 05:00:02 2009
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "car_adaptor_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'car_adaptor_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CarAdaptor[] = {

 // content:
       4,       // revision
       0,       // classname
       2,   14, // classinfo
       5,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
      36,   11,
     352,   52,

 // signals: signature, parameters, type, tag, flags
     373,  372,  372,  372, 0x05,

 // slots: signature, parameters, type, tag, flags
     383,  372,  372,  372, 0x0a,
     396,  372,  372,  372, 0x0a,
     409,  372,  372,  372, 0x0a,
     420,  372,  372,  372, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CarAdaptor[] = {
    "CarAdaptor\0com.redflag.carInterface\0"
    "D-Bus Interface\0"
    "  <interface name=\"com.redflag.carInterface\">\n    <method name=\"ac"
    "celerate\">\n      <method name=\"dccelerate\">\n        <method name="
    "\"turnLeft\">\n          <method name=\"turnRight\">\n            <sig"
    "nal name=\"crashed\"/>\n          </method>\n        </method>\n      "
    "</method>\n    </method>\n  </interface>\n\0"
    "D-Bus Introspection\0\0crashed()\0"
    "accelerate()\0dccelerate()\0turnLeft()\0"
    "turnRight()\0"
};

const QMetaObject CarAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_CarAdaptor,
      qt_meta_data_CarAdaptor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CarAdaptor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CarAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CarAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CarAdaptor))
        return static_cast<void*>(const_cast< CarAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int CarAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: crashed(); break;
        case 1: accelerate(); break;
        case 2: dccelerate(); break;
        case 3: turnLeft(); break;
        case 4: turnRight(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CarAdaptor::crashed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
