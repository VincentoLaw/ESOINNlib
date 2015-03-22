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
    QByteArrayData data[10];
    char stringdata[125];
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
QT_MOC_LITERAL(3, 41, 14), // "QList<QString>"
QT_MOC_LITERAL(4, 56, 2), // "im"
QT_MOC_LITERAL(5, 59, 12), // "pointedImage"
QT_MOC_LITERAL(6, 72, 13), // "loadStructure"
QT_MOC_LITERAL(7, 86, 13), // "saveStructure"
QT_MOC_LITERAL(8, 100, 10), // "loadVector"
QT_MOC_LITERAL(9, 111, 13) // "dimensionsCnt"

    },
    "dataExchanger\0structureData\0esoinnParams\0"
    "QList<QString>\0im\0pointedImage\0"
    "loadStructure\0saveStructure\0loadVector\0"
    "dimensionsCnt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dataExchanger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095103,
       2, 0x80000000 | 3, 0x0009510b,
       4, QMetaType::QUrl, 0x00095003,
       5, QMetaType::QUrl, 0x00095103,
       6, QMetaType::QUrl, 0x00095103,
       7, QMetaType::QUrl, 0x00095103,
       8, QMetaType::QUrl, 0x00095103,
       9, QMetaType::Int, 0x00095103,

       0        // eod
};

void dataExchanger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
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
        case 1: *reinterpret_cast< QList<QString>*>(_v) = esoinnParams(); break;
        case 2: *reinterpret_cast< QUrl*>(_v) = im(); break;
        case 3: *reinterpret_cast< QUrl*>(_v) = pointedImage(); break;
        case 4: *reinterpret_cast< QUrl*>(_v) = loadStructure(); break;
        case 5: *reinterpret_cast< QUrl*>(_v) = saveStructure(); break;
        case 6: *reinterpret_cast< QUrl*>(_v) = loadVector(); break;
        case 7: *reinterpret_cast< int*>(_v) = dimensionsCnt(); break;
        default: break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setStructureData(*reinterpret_cast< QString*>(_v)); break;
        case 1: setEsoinnParams(*reinterpret_cast< QList<QString>*>(_v)); break;
        case 2: sim(*reinterpret_cast< QUrl*>(_v)); break;
        case 3: setPointedImage(*reinterpret_cast< QUrl*>(_v)); break;
        case 4: setLoadStructure(*reinterpret_cast< QUrl*>(_v)); break;
        case 5: setSaveStructure(*reinterpret_cast< QUrl*>(_v)); break;
        case 6: setLoadVector(*reinterpret_cast< QUrl*>(_v)); break;
        case 7: setDimensionsCnt(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
