/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[66];
    char stringdata0[1332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "keyEventCaptured"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 40, 5), // "event"
QT_MOC_LITERAL(5, 46, 12), // "playerChange"
QT_MOC_LITERAL(6, 59, 13), // "currentPlayer"
QT_MOC_LITERAL(7, 73, 18), // "on_LoadBtn_clicked"
QT_MOC_LITERAL(8, 92, 19), // "on_storeBtn_clicked"
QT_MOC_LITERAL(9, 112, 17), // "on_WinBtn_clicked"
QT_MOC_LITERAL(10, 130, 19), // "on_clearBtn_clicked"
QT_MOC_LITERAL(11, 150, 19), // "on_judgeBtn_clicked"
QT_MOC_LITERAL(12, 170, 7), // "checked"
QT_MOC_LITERAL(13, 178, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(14, 200, 24), // "on_pieceTree_itemClicked"
QT_MOC_LITERAL(15, 225, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(16, 242, 4), // "item"
QT_MOC_LITERAL(17, 247, 6), // "column"
QT_MOC_LITERAL(18, 254, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(19, 278, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(20, 311, 5), // "value"
QT_MOC_LITERAL(21, 317, 16), // "on_Begin_clicked"
QT_MOC_LITERAL(22, 334, 14), // "on_End_clicked"
QT_MOC_LITERAL(23, 349, 19), // "on_leftFive_clicked"
QT_MOC_LITERAL(24, 369, 18), // "on_leftOne_clicked"
QT_MOC_LITERAL(25, 388, 20), // "on_rightFive_clicked"
QT_MOC_LITERAL(26, 409, 19), // "on_rightOne_clicked"
QT_MOC_LITERAL(27, 429, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(28, 451, 24), // "on_toolButton_27_clicked"
QT_MOC_LITERAL(29, 476, 19), // "on_addDSBtn_clicked"
QT_MOC_LITERAL(30, 496, 31), // "on_pieceTree_currentItemChanged"
QT_MOC_LITERAL(31, 528, 7), // "current"
QT_MOC_LITERAL(32, 536, 8), // "previous"
QT_MOC_LITERAL(33, 545, 39), // "on_pieceTree_customContextMen..."
QT_MOC_LITERAL(34, 585, 3), // "pos"
QT_MOC_LITERAL(35, 589, 23), // "on_toolButton_4_clicked"
QT_MOC_LITERAL(36, 613, 24), // "on_toolButton_19_clicked"
QT_MOC_LITERAL(37, 638, 23), // "on_toolButton_9_clicked"
QT_MOC_LITERAL(38, 662, 25), // "on_actiontuichu_triggered"
QT_MOC_LITERAL(39, 688, 25), // "on_actionguanyu_triggered"
QT_MOC_LITERAL(40, 714, 19), // "on_action_triggered"
QT_MOC_LITERAL(41, 734, 29), // "on_actionsearchStep_triggered"
QT_MOC_LITERAL(42, 764, 25), // "on_actioncunchu_triggered"
QT_MOC_LITERAL(43, 790, 23), // "on_actionduqu_triggered"
QT_MOC_LITERAL(44, 814, 27), // "on_actionjudgeWin_triggered"
QT_MOC_LITERAL(45, 842, 27), // "on_actionnextStep_triggered"
QT_MOC_LITERAL(46, 870, 23), // "on_actionundo_triggered"
QT_MOC_LITERAL(47, 894, 23), // "on_actionredo_triggered"
QT_MOC_LITERAL(48, 918, 23), // "on_actionjump_triggered"
QT_MOC_LITERAL(49, 942, 25), // "on_actiondelete_triggered"
QT_MOC_LITERAL(50, 968, 22), // "on_actiontry_triggered"
QT_MOC_LITERAL(51, 991, 27), // "on_actionxuandian_triggered"
QT_MOC_LITERAL(52, 1019, 24), // "on_toolButton_22_clicked"
QT_MOC_LITERAL(53, 1044, 21), // "on_BAlwaysBtn_clicked"
QT_MOC_LITERAL(54, 1066, 21), // "on_WAlwaysBtn_clicked"
QT_MOC_LITERAL(55, 1088, 24), // "on_toolButton_25_clicked"
QT_MOC_LITERAL(56, 1113, 23), // "on_RetractPiece_clicked"
QT_MOC_LITERAL(57, 1137, 20), // "on_giveUpBtn_clicked"
QT_MOC_LITERAL(58, 1158, 24), // "on_toolButton_20_clicked"
QT_MOC_LITERAL(59, 1183, 19), // "on_autoPlay_clicked"
QT_MOC_LITERAL(60, 1203, 20), // "on_setting_triggered"
QT_MOC_LITERAL(61, 1224, 16), // "on_AIBtn_clicked"
QT_MOC_LITERAL(62, 1241, 24), // "on_toolButton_11_clicked"
QT_MOC_LITERAL(63, 1266, 20), // "on_AIPlayBtn_clicked"
QT_MOC_LITERAL(64, 1287, 18), // "on_AIJudge_clicked"
QT_MOC_LITERAL(65, 1306, 25) // "on_actionfindDS_triggered"

    },
    "MainWindow\0keyEventCaptured\0\0QKeyEvent*\0"
    "event\0playerChange\0currentPlayer\0"
    "on_LoadBtn_clicked\0on_storeBtn_clicked\0"
    "on_WinBtn_clicked\0on_clearBtn_clicked\0"
    "on_judgeBtn_clicked\0checked\0"
    "on_toolButton_clicked\0on_pieceTree_itemClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_toolButton_2_clicked\0"
    "on_horizontalSlider_valueChanged\0value\0"
    "on_Begin_clicked\0on_End_clicked\0"
    "on_leftFive_clicked\0on_leftOne_clicked\0"
    "on_rightFive_clicked\0on_rightOne_clicked\0"
    "on_pushButton_clicked\0on_toolButton_27_clicked\0"
    "on_addDSBtn_clicked\0on_pieceTree_currentItemChanged\0"
    "current\0previous\0"
    "on_pieceTree_customContextMenuRequested\0"
    "pos\0on_toolButton_4_clicked\0"
    "on_toolButton_19_clicked\0"
    "on_toolButton_9_clicked\0"
    "on_actiontuichu_triggered\0"
    "on_actionguanyu_triggered\0on_action_triggered\0"
    "on_actionsearchStep_triggered\0"
    "on_actioncunchu_triggered\0"
    "on_actionduqu_triggered\0"
    "on_actionjudgeWin_triggered\0"
    "on_actionnextStep_triggered\0"
    "on_actionundo_triggered\0on_actionredo_triggered\0"
    "on_actionjump_triggered\0"
    "on_actiondelete_triggered\0"
    "on_actiontry_triggered\0"
    "on_actionxuandian_triggered\0"
    "on_toolButton_22_clicked\0on_BAlwaysBtn_clicked\0"
    "on_WAlwaysBtn_clicked\0on_toolButton_25_clicked\0"
    "on_RetractPiece_clicked\0on_giveUpBtn_clicked\0"
    "on_toolButton_20_clicked\0on_autoPlay_clicked\0"
    "on_setting_triggered\0on_AIBtn_clicked\0"
    "on_toolButton_11_clicked\0on_AIPlayBtn_clicked\0"
    "on_AIJudge_clicked\0on_actionfindDS_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      54,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  284,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,  287,    2, 0x0a /* Public */,
       7,    0,  290,    2, 0x08 /* Private */,
       8,    0,  291,    2, 0x08 /* Private */,
       9,    0,  292,    2, 0x08 /* Private */,
      10,    0,  293,    2, 0x08 /* Private */,
      11,    1,  294,    2, 0x08 /* Private */,
      13,    0,  297,    2, 0x08 /* Private */,
      14,    2,  298,    2, 0x08 /* Private */,
      18,    0,  303,    2, 0x08 /* Private */,
      19,    1,  304,    2, 0x08 /* Private */,
      21,    0,  307,    2, 0x08 /* Private */,
      22,    0,  308,    2, 0x08 /* Private */,
      23,    0,  309,    2, 0x08 /* Private */,
      24,    0,  310,    2, 0x08 /* Private */,
      25,    0,  311,    2, 0x08 /* Private */,
      26,    0,  312,    2, 0x08 /* Private */,
      27,    0,  313,    2, 0x08 /* Private */,
      28,    0,  314,    2, 0x08 /* Private */,
      29,    0,  315,    2, 0x08 /* Private */,
      30,    2,  316,    2, 0x08 /* Private */,
      33,    1,  321,    2, 0x08 /* Private */,
      35,    1,  324,    2, 0x08 /* Private */,
       9,    1,  327,    2, 0x08 /* Private */,
      36,    0,  330,    2, 0x08 /* Private */,
      37,    0,  331,    2, 0x08 /* Private */,
      38,    0,  332,    2, 0x08 /* Private */,
      39,    0,  333,    2, 0x08 /* Private */,
      40,    0,  334,    2, 0x08 /* Private */,
      41,    0,  335,    2, 0x08 /* Private */,
      42,    0,  336,    2, 0x08 /* Private */,
      43,    0,  337,    2, 0x08 /* Private */,
      44,    0,  338,    2, 0x08 /* Private */,
      45,    0,  339,    2, 0x08 /* Private */,
      46,    0,  340,    2, 0x08 /* Private */,
      47,    0,  341,    2, 0x08 /* Private */,
      48,    0,  342,    2, 0x08 /* Private */,
      49,    0,  343,    2, 0x08 /* Private */,
      50,    1,  344,    2, 0x08 /* Private */,
      51,    1,  347,    2, 0x08 /* Private */,
      52,    0,  350,    2, 0x08 /* Private */,
      53,    0,  351,    2, 0x08 /* Private */,
      54,    0,  352,    2, 0x08 /* Private */,
      55,    0,  353,    2, 0x08 /* Private */,
      56,    0,  354,    2, 0x08 /* Private */,
      57,    0,  355,    2, 0x08 /* Private */,
      58,    0,  356,    2, 0x08 /* Private */,
      59,    1,  357,    2, 0x08 /* Private */,
      60,    0,  360,    2, 0x08 /* Private */,
      61,    0,  361,    2, 0x08 /* Private */,
      62,    0,  362,    2, 0x08 /* Private */,
      63,    1,  363,    2, 0x08 /* Private */,
      64,    0,  366,    2, 0x08 /* Private */,
      65,    0,  367,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   31,   32,
    QMetaType::Void, QMetaType::QPoint,   34,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyEventCaptured((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->playerChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_LoadBtn_clicked(); break;
        case 3: _t->on_storeBtn_clicked(); break;
        case 4: _t->on_WinBtn_clicked(); break;
        case 5: _t->on_clearBtn_clicked(); break;
        case 6: _t->on_judgeBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_toolButton_clicked(); break;
        case 8: _t->on_pieceTree_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->on_toolButton_2_clicked(); break;
        case 10: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_Begin_clicked(); break;
        case 12: _t->on_End_clicked(); break;
        case 13: _t->on_leftFive_clicked(); break;
        case 14: _t->on_leftOne_clicked(); break;
        case 15: _t->on_rightFive_clicked(); break;
        case 16: _t->on_rightOne_clicked(); break;
        case 17: _t->on_pushButton_clicked(); break;
        case 18: _t->on_toolButton_27_clicked(); break;
        case 19: _t->on_addDSBtn_clicked(); break;
        case 20: _t->on_pieceTree_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 21: _t->on_pieceTree_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 22: _t->on_toolButton_4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->on_WinBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_toolButton_19_clicked(); break;
        case 25: _t->on_toolButton_9_clicked(); break;
        case 26: _t->on_actiontuichu_triggered(); break;
        case 27: _t->on_actionguanyu_triggered(); break;
        case 28: _t->on_action_triggered(); break;
        case 29: _t->on_actionsearchStep_triggered(); break;
        case 30: _t->on_actioncunchu_triggered(); break;
        case 31: _t->on_actionduqu_triggered(); break;
        case 32: _t->on_actionjudgeWin_triggered(); break;
        case 33: _t->on_actionnextStep_triggered(); break;
        case 34: _t->on_actionundo_triggered(); break;
        case 35: _t->on_actionredo_triggered(); break;
        case 36: _t->on_actionjump_triggered(); break;
        case 37: _t->on_actiondelete_triggered(); break;
        case 38: _t->on_actiontry_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->on_actionxuandian_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->on_toolButton_22_clicked(); break;
        case 41: _t->on_BAlwaysBtn_clicked(); break;
        case 42: _t->on_WAlwaysBtn_clicked(); break;
        case 43: _t->on_toolButton_25_clicked(); break;
        case 44: _t->on_RetractPiece_clicked(); break;
        case 45: _t->on_giveUpBtn_clicked(); break;
        case 46: _t->on_toolButton_20_clicked(); break;
        case 47: _t->on_autoPlay_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->on_setting_triggered(); break;
        case 49: _t->on_AIBtn_clicked(); break;
        case 50: _t->on_toolButton_11_clicked(); break;
        case 51: _t->on_AIPlayBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->on_AIJudge_clicked(); break;
        case 53: _t->on_actionfindDS_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::keyEventCaptured)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 54)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 54;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 54)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 54;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::keyEventCaptured(QKeyEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
