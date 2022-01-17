/****************************************************************************
** Meta object code from reading C++ file 'ImageCapture.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ImageCapture.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageCapture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CImageCapture_t {
    QByteArrayData data[15];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CImageCapture_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CImageCapture_t qt_meta_stringdata_CImageCapture = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CImageCapture"
QT_MOC_LITERAL(1, 14, 17), // "SendLeftAlgoImage"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "Mat"
QT_MOC_LITERAL(4, 37, 13), // "OriginalImage"
QT_MOC_LITERAL(5, 51, 11), // "RenderImage"
QT_MOC_LITERAL(6, 63, 5), // "index"
QT_MOC_LITERAL(7, 69, 3), // "bOK"
QT_MOC_LITERAL(8, 73, 18), // "SendRightAlgoImage"
QT_MOC_LITERAL(9, 92, 16), // "SendCaptureImage"
QT_MOC_LITERAL(10, 109, 3), // "img"
QT_MOC_LITERAL(11, 113, 12), // "e_CameraType"
QT_MOC_LITERAL(12, 126, 4), // "type"
QT_MOC_LITERAL(13, 131, 20), // "ReceiveLeftAlgoImage"
QT_MOC_LITERAL(14, 152, 21) // "ReceiveRightAlgoImage"

    },
    "CImageCapture\0SendLeftAlgoImage\0\0Mat\0"
    "OriginalImage\0RenderImage\0index\0bOK\0"
    "SendRightAlgoImage\0SendCaptureImage\0"
    "img\0e_CameraType\0type\0ReceiveLeftAlgoImage\0"
    "ReceiveRightAlgoImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CImageCapture[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   39,    2, 0x06 /* Public */,
       8,    4,   48,    2, 0x06 /* Public */,
       9,    2,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    4,   62,    2, 0x08 /* Private */,
      14,    4,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int, QMetaType::Bool,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int, QMetaType::Bool,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 11,   10,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int, QMetaType::Bool,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int, QMetaType::Bool,    4,    5,    6,    7,

       0        // eod
};

void CImageCapture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CImageCapture *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendLeftAlgoImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: _t->SendRightAlgoImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: _t->SendCaptureImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< e_CameraType(*)>(_a[2]))); break;
        case 3: _t->ReceiveLeftAlgoImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 4: _t->ReceiveRightAlgoImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CImageCapture::*)(Mat , Mat , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendLeftAlgoImage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CImageCapture::*)(Mat , Mat , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendRightAlgoImage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CImageCapture::*)(Mat , e_CameraType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CImageCapture::SendCaptureImage)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CImageCapture::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_CImageCapture.data,
    qt_meta_data_CImageCapture,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CImageCapture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CImageCapture::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CImageCapture.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CImageCapture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CImageCapture::SendLeftAlgoImage(Mat _t1, Mat _t2, int _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CImageCapture::SendRightAlgoImage(Mat _t1, Mat _t2, int _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CImageCapture::SendCaptureImage(Mat _t1, e_CameraType _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
