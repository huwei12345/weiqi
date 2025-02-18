/****************************************************************************
** Meta object code from reading C++ file 'kata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../kata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Kata_t {
    QByteArrayData data[24];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Kata_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Kata_t qt_meta_stringdata_Kata = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Kata"
QT_MOC_LITERAL(1, 5, 17), // "getAIPieceSuccess"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "Piece*"
QT_MOC_LITERAL(4, 31, 5), // "piece"
QT_MOC_LITERAL(5, 37, 21), // "calculateScoreSuccess"
QT_MOC_LITERAL(6, 59, 25), // "calculateEndResultSuccess"
QT_MOC_LITERAL(7, 85, 19), // "analyzeResultUpdate"
QT_MOC_LITERAL(8, 105, 9), // "startKata"
QT_MOC_LITERAL(9, 115, 10), // "getAIPiece"
QT_MOC_LITERAL(10, 126, 5), // "Piece"
QT_MOC_LITERAL(11, 132, 8), // "nowPiece"
QT_MOC_LITERAL(12, 141, 5), // "color"
QT_MOC_LITERAL(13, 147, 14), // "calculateScore"
QT_MOC_LITERAL(14, 162, 28), // "std::shared_ptr<SGFTreeNode>"
QT_MOC_LITERAL(15, 191, 4), // "node"
QT_MOC_LITERAL(16, 196, 10), // "JudgeInfo*"
QT_MOC_LITERAL(17, 207, 4), // "info"
QT_MOC_LITERAL(18, 212, 17), // "calculateEndScore"
QT_MOC_LITERAL(19, 230, 16), // "startKataAnalyze"
QT_MOC_LITERAL(20, 247, 25), // "ThreadSafeQueue<QString>*"
QT_MOC_LITERAL(21, 273, 5), // "queue"
QT_MOC_LITERAL(22, 279, 15), // "stopKataAnalyze"
QT_MOC_LITERAL(23, 295, 12) // "playOnePiece"

    },
    "Kata\0getAIPieceSuccess\0\0Piece*\0piece\0"
    "calculateScoreSuccess\0calculateEndResultSuccess\0"
    "analyzeResultUpdate\0startKata\0getAIPiece\0"
    "Piece\0nowPiece\0color\0calculateScore\0"
    "std::shared_ptr<SGFTreeNode>\0node\0"
    "JudgeInfo*\0info\0calculateEndScore\0"
    "startKataAnalyze\0ThreadSafeQueue<QString>*\0"
    "queue\0stopKataAnalyze\0playOnePiece"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Kata[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   75,    2, 0x0a /* Public */,
       9,    2,   76,    2, 0x0a /* Public */,
      13,    2,   81,    2, 0x0a /* Public */,
      18,    2,   86,    2, 0x0a /* Public */,
      19,    2,   91,    2, 0x0a /* Public */,
      22,    0,   96,    2, 0x0a /* Public */,
      23,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 20,   15,   21,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    4,

       0        // eod
};

void Kata::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Kata *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getAIPieceSuccess((*reinterpret_cast< Piece*(*)>(_a[1]))); break;
        case 1: _t->calculateScoreSuccess(); break;
        case 2: _t->calculateEndResultSuccess(); break;
        case 3: _t->analyzeResultUpdate(); break;
        case 4: { int _r = _t->startKata();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->getAIPiece((*reinterpret_cast< Piece(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->calculateScore((*reinterpret_cast< std::shared_ptr<SGFTreeNode>(*)>(_a[1])),(*reinterpret_cast< JudgeInfo*(*)>(_a[2]))); break;
        case 7: _t->calculateEndScore((*reinterpret_cast< std::shared_ptr<SGFTreeNode>(*)>(_a[1])),(*reinterpret_cast< JudgeInfo*(*)>(_a[2]))); break;
        case 8: _t->startKataAnalyze((*reinterpret_cast< std::shared_ptr<SGFTreeNode>(*)>(_a[1])),(*reinterpret_cast< ThreadSafeQueue<QString>*(*)>(_a[2]))); break;
        case 9: _t->stopKataAnalyze(); break;
        case 10: _t->playOnePiece((*reinterpret_cast< Piece(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Piece >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< JudgeInfo* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< JudgeInfo* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Piece >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Kata::*)(Piece * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kata::getAIPieceSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Kata::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kata::calculateScoreSuccess)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Kata::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kata::calculateEndResultSuccess)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Kata::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kata::analyzeResultUpdate)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Kata::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Kata.data,
    qt_meta_data_Kata,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Kata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kata::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Kata.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Kata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Kata::getAIPieceSuccess(Piece * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Kata::calculateScoreSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Kata::calculateEndResultSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Kata::analyzeResultUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
