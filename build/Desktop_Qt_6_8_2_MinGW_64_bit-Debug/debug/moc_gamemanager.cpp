/****************************************************************************
** Meta object code from reading C++ file 'gamemanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../gamemanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11GameManagerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11GameManagerE = QtMocHelpers::stringData(
    "GameManager",
    "showMenuPage",
    "",
    "showStartPage",
    "LevelType",
    "level",
    "showTutorialPage",
    "startLevel",
    "handleLevelCompletion",
    "completedLevel",
    "onLevel1Completed",
    "onLevel2Completed",
    "onLevel3Completed",
    "onLevel4Completed",
    "onLevel5Completed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11GameManagerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    1,   75,    2, 0x08,    2 /* Private */,
       6,    0,   78,    2, 0x08,    4 /* Private */,
       7,    1,   79,    2, 0x08,    5 /* Private */,
       8,    1,   82,    2, 0x08,    7 /* Private */,
      10,    0,   85,    2, 0x08,    9 /* Private */,
      11,    0,   86,    2, 0x08,   10 /* Private */,
      12,    0,   87,    2, 0x08,   11 /* Private */,
      13,    0,   88,    2, 0x08,   12 /* Private */,
      14,    0,   89,    2, 0x08,   13 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN11GameManagerE.offsetsAndSizes,
    qt_meta_data_ZN11GameManagerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11GameManagerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameManager, std::true_type>,
        // method 'showMenuPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStartPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<LevelType, std::false_type>,
        // method 'showTutorialPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<LevelType, std::false_type>,
        // method 'handleLevelCompletion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<LevelType, std::false_type>,
        // method 'onLevel1Completed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLevel2Completed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLevel3Completed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLevel4Completed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLevel5Completed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GameManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->showMenuPage(); break;
        case 1: _t->showStartPage((*reinterpret_cast< std::add_pointer_t<LevelType>>(_a[1]))); break;
        case 2: _t->showTutorialPage(); break;
        case 3: _t->startLevel((*reinterpret_cast< std::add_pointer_t<LevelType>>(_a[1]))); break;
        case 4: _t->handleLevelCompletion((*reinterpret_cast< std::add_pointer_t<LevelType>>(_a[1]))); break;
        case 5: _t->onLevel1Completed(); break;
        case 6: _t->onLevel2Completed(); break;
        case 7: _t->onLevel3Completed(); break;
        case 8: _t->onLevel4Completed(); break;
        case 9: _t->onLevel5Completed(); break;
        default: ;
        }
    }
}

const QMetaObject *GameManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11GameManagerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
