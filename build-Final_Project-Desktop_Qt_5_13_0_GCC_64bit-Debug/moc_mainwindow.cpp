/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Final_Project/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_convertFormat_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 27), // "on_changeResolution_clicked"
QT_MOC_LITERAL(4, 65, 25), // "on_addRemoveAudio_clicked"
QT_MOC_LITERAL(5, 91, 24), // "on_connectVideos_clicked"
QT_MOC_LITERAL(6, 116, 26), // "on_deletePartVideo_clicked"
QT_MOC_LITERAL(7, 143, 23), // "on_changeVolume_clicked"
QT_MOC_LITERAL(8, 167, 15), // "on_exit_clicked"
QT_MOC_LITERAL(9, 183, 33), // "on_horizontalProgress_sliderM..."
QT_MOC_LITERAL(10, 217, 8), // "position"
QT_MOC_LITERAL(11, 226, 31), // "on_horizontalVolume_sliderMoved"
QT_MOC_LITERAL(12, 258, 15), // "on_open_clicked"
QT_MOC_LITERAL(13, 274, 15), // "on_play_clicked"
QT_MOC_LITERAL(14, 290, 16), // "on_pause_clicked"
QT_MOC_LITERAL(15, 307, 15), // "on_stop_clicked"
QT_MOC_LITERAL(16, 323, 18), // "on_positionChanged"
QT_MOC_LITERAL(17, 342, 18) // "on_durationChanged"

    },
    "MainWindow\0on_convertFormat_clicked\0"
    "\0on_changeResolution_clicked\0"
    "on_addRemoveAudio_clicked\0"
    "on_connectVideos_clicked\0"
    "on_deletePartVideo_clicked\0"
    "on_changeVolume_clicked\0on_exit_clicked\0"
    "on_horizontalProgress_sliderMoved\0"
    "position\0on_horizontalVolume_sliderMoved\0"
    "on_open_clicked\0on_play_clicked\0"
    "on_pause_clicked\0on_stop_clicked\0"
    "on_positionChanged\0on_durationChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    1,   96,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    0,  103,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      17,    1,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_convertFormat_clicked(); break;
        case 1: _t->on_changeResolution_clicked(); break;
        case 2: _t->on_addRemoveAudio_clicked(); break;
        case 3: _t->on_connectVideos_clicked(); break;
        case 4: _t->on_deletePartVideo_clicked(); break;
        case 5: _t->on_changeVolume_clicked(); break;
        case 6: _t->on_exit_clicked(); break;
        case 7: _t->on_horizontalProgress_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_horizontalVolume_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_open_clicked(); break;
        case 10: _t->on_play_clicked(); break;
        case 11: _t->on_pause_clicked(); break;
        case 12: _t->on_stop_clicked(); break;
        case 13: _t->on_positionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_durationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
