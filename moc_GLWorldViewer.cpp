/****************************************************************************
** Meta object code from reading C++ file 'GLWorldViewer.h'
**
** Created: Fri Mar 9 15:27:18 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GLWorldViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWorldViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWorldViewer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      33,   14,   14,   14, 0x0a,
      40,   14,   14,   14, 0x0a,
      56,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWorldViewer[] = {
    "GLWorldViewer\0\0createIndividue()\0"
    "turn()\0testIndividue()\0startPauseTimer()\0"
};

const QMetaObject GLWorldViewer::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWorldViewer,
      qt_meta_data_GLWorldViewer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWorldViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWorldViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWorldViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWorldViewer))
        return static_cast<void*>(const_cast< GLWorldViewer*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWorldViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createIndividue(); break;
        case 1: turn(); break;
        case 2: testIndividue(); break;
        case 3: startPauseTimer(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
