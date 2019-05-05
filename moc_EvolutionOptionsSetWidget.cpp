/****************************************************************************
** Meta object code from reading C++ file 'EvolutionOptionsSetWidget.h'
**
** Created: Thu Mar 8 13:46:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EvolutionOptionsSetWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EvolutionOptionsSetWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EvolutionOptionsSetWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,
      54,   26,   26,   26, 0x0a,
      81,   26,   26,   26, 0x0a,
     108,   26,   26,   26, 0x0a,
     139,   26,   26,   26, 0x0a,
     169,   26,   26,   26, 0x0a,
     204,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EvolutionOptionsSetWidget[] = {
    "EvolutionOptionsSetWidget\0\0"
    "populationSizeChanged(int)\0"
    "generatorsSizeChanged(int)\0"
    "mutationTaxChanged(double)\0"
    "populationTypeChanged(QString)\0"
    "selectionTypeChanged(QString)\0"
    "allowRessurectionStateChanged(int)\0"
    "crossMutationChanged(int)\0"
};

const QMetaObject EvolutionOptionsSetWidget::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_EvolutionOptionsSetWidget,
      qt_meta_data_EvolutionOptionsSetWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EvolutionOptionsSetWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EvolutionOptionsSetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EvolutionOptionsSetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EvolutionOptionsSetWidget))
        return static_cast<void*>(const_cast< EvolutionOptionsSetWidget*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int EvolutionOptionsSetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: populationSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: generatorsSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: mutationTaxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: populationTypeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: selectionTypeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: allowRessurectionStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: crossMutationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
