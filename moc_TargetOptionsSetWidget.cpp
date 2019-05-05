/****************************************************************************
** Meta object code from reading C++ file 'TargetOptionsSetWidget.h'
**
** Created: Fri Mar 9 15:27:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TargetOptionsSetWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TargetOptionsSetWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TargetOptionsSetWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      52,   23,   23,   23, 0x0a,
      83,   23,   23,   23, 0x0a,
     114,   23,   23,   23, 0x0a,
     145,   23,   23,   23, 0x0a,
     175,   23,   23,   23, 0x0a,
     205,   23,   23,   23, 0x0a,
     230,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TargetOptionsSetWidget[] = {
    "TargetOptionsSetWidget\0\0"
    "terrainTypeChanged(QString)\0"
    "initialPositionChanged(double)\0"
    "maxTestIntervalChanged(double)\0"
    "wheelsKickDiscountChanged(int)\0"
    "bodyCrashDiscountChanged(int)\0"
    "loopCountDiscountChanged(int)\0"
    "hasObstaclesChanged(int)\0"
    "minXVelocityChanged(double)\0"
};

const QMetaObject TargetOptionsSetWidget::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_TargetOptionsSetWidget,
      qt_meta_data_TargetOptionsSetWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TargetOptionsSetWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TargetOptionsSetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TargetOptionsSetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TargetOptionsSetWidget))
        return static_cast<void*>(const_cast< TargetOptionsSetWidget*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int TargetOptionsSetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: terrainTypeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: initialPositionChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: maxTestIntervalChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: wheelsKickDiscountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: bodyCrashDiscountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: loopCountDiscountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: hasObstaclesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: minXVelocityChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
