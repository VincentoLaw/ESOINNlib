/****************************************************************************
** Meta object code from reading C++ file 'dataExchanger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ESOINNlib/dataExchanger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataExchanger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dataExchanger_t {
    QByteArrayData data[5];
    char stringdata[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dataExchanger_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dataExchanger_t qt_meta_stringdata_dataExchanger = {
    {
QT_MOC_LITERAL(0, 0, 13), // "dataExchanger"
QT_MOC_LITERAL(1, 14, 13), // "structureData"
QT_MOC_LITERAL(2, 28, 12), // "esoinnParams"
QT_MOC_LITERAL(3, 41, 13), // "QList<double>"
QT_MOC_LITERAL(4, 55, 2) // "im"

    },
    "dataExchanger\0structureData\0esoinnParams\0"
    "QList<double>\0im"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dataExchanger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095103,
       2, 0x80000000 | 3, 0x0009510b,
       4, QMetaType::QUrl, 0x00095003,

       0        // eod
};

void dataExchanger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
        }
    }

    Q_UNUSED(_o);
}

const QMetaObject dataExchanger::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dataExchanger.data,
      qt_meta_data_dataExchanger,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *dataExchanger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dataExchanger::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_dataExchanger.stringdata))
        return static_cast<void*>(const_cast< dataExchanger*>(this));
    return QObject::qt_metacast(_clname);
}

int dataExchanger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = structureData(); break;
        case 1: *reinterpret_cast< QList<double>*>(_v) = esoinnParams(); break;
        case 2: *reinterpret_cast< QUrl*>(_v) = im(); break;
        default: break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setStructureData(*reinterpret_cast< QString*>(_v)); break;
        case 1: setEsoinnParams(*reinterpret_cast< QList<double>*>(_v)); break;
        case 2: sim(*reinterpret_cast< QUrl*>(_v)); break;
        default: break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
