/****************************************************************************
** Meta object code from reading C++ file 'newDialog.h'
**
** Created: Tue Sep 23 16:47:20 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_NewDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NewDialog[] = {
    "NewDialog\0\0lineEditTextChanged(QString)\0"
};

const QMetaObject NewDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewDialog,
      qt_meta_data_NewDialog, 0 }
};

const QMetaObject *NewDialog::metaObject() const
{
    return &staticMetaObject;
}

void *NewDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewDialog))
	return static_cast<void*>(const_cast< NewDialog*>(this));
    if (!strcmp(_clname, "Ui::Dialog"))
	return static_cast< Ui::Dialog*>(const_cast< NewDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: lineEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
