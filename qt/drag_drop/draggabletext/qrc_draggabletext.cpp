/****************************************************************************
** Resource object code
**
** Created: Fri Jun 19 10:37:32 2009
**      by: The Resource Compiler for Qt version 4.4.0
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qglobal.h>

static const unsigned char qt_resource_data[] = {
  // /home/pwp/programming/qt/drag_drop/draggabletext/words.txt
  0x0,0x0,0x0,0x11,
  0x31,
  0x32,0x33,0x20,0xa,0x34,0x35,0x36,0xa,0x31,0x32,0x33,0x20,0x34,0x35,0x36,0xa,
  
  
};

static const unsigned char qt_resource_name[] = {
  // words.txt
  0x0,0x9,
  0x8,0xb6,0xa7,0x34,
  0x0,0x77,
  0x0,0x6f,0x0,0x72,0x0,0x64,0x0,0x73,0x0,0x2e,0x0,0x74,0x0,0x78,0x0,0x74,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/words.txt
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

QT_BEGIN_NAMESPACE

extern bool qRegisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

extern bool qUnregisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

QT_END_NAMESPACE


int QT_MANGLE_NAMESPACE(qInitResources_draggabletext)()
{
    QT_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_draggabletext))

int QT_MANGLE_NAMESPACE(qCleanupResources_draggabletext)()
{
    QT_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_DESTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qCleanupResources_draggabletext))

