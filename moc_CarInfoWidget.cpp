/****************************************************************************
** Meta object code from reading C++ file 'CarInfoWidget.h'
**
** Created: Fri Mar 9 15:17:46 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CarInfoWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CarInfoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CarInfoWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CarInfoWidget[] = {
    "CarInfoWidget\0"
};

const QMetaObject CarInfoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CarInfoWidget,
      qt_meta_data_CarInfoWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CarInfoWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CarInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CarInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CarInfoWidget))
        return static_cast<void*>(const_cast< CarInfoWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CarInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
