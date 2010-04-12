/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created: Mon Jun 15 21:41:37 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Window[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x08,
      34,   27,    7,    7, 0x08,
      83,    7,    7,    7, 0x08,
      97,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Window[] = {
    "Window\0\0index\0setIcon(int)\0reason\0"
    "iconActivated(QSystemTrayIcon::ActivationReason)\0"
    "showMessage()\0messageClicked()\0"
};

const QMetaObject Window::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Window,
      qt_meta_data_Window, 0 }
};

const QMetaObject *Window::metaObject() const
{
    return &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window))
	return static_cast<void*>(const_cast< Window*>(this));
    return QDialog::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setIcon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 2: showMessage(); break;
        case 3: messageClicked(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
