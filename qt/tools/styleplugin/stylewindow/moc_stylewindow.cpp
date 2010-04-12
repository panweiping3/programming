/****************************************************************************
** Meta object code from reading C++ file 'stylewindow.h'
**
** Created: Fri Jul 17 19:54:47 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stylewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stylewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StyleWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_StyleWindow[] = {
    "StyleWindow\0"
};

const QMetaObject StyleWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StyleWindow,
      qt_meta_data_StyleWindow, 0 }
};

const QMetaObject *StyleWindow::metaObject() const
{
    return &staticMetaObject;
}

void *StyleWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StyleWindow))
	return static_cast<void*>(const_cast< StyleWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int StyleWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
