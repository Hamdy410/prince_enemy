/****************************************************************************
** Meta object code from reading C++ file 'enemy.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../enemy.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enemy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN5EnemyE_t {};
} // unnamed namespace

template <> constexpr inline auto Enemy::qt_create_metaobjectdata<qt_meta_tag_ZN5EnemyE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Enemy",
        "positionChanged",
        "",
        "visualChanged",
        "stateChanged",
        "Enemy::State",
        "state",
        "died",
        "handleAnimationCompleted",
        "stateName",
        "State",
        "WALKRIGHT",
        "ATTACKRIGHT",
        "DIERIGHT",
        "WALKLEFT",
        "ATTACKLEFT",
        "DIELEFT"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'positionChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'visualChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stateChanged'
        QtMocHelpers::SignalData<void(Enemy::State)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'died'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleAnimationCompleted'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'State'
        QtMocHelpers::EnumData<State>(10, 10, QMC::EnumFlags{}).add({
            {   11, State::WALKRIGHT },
            {   12, State::ATTACKRIGHT },
            {   13, State::DIERIGHT },
            {   14, State::WALKLEFT },
            {   15, State::ATTACKLEFT },
            {   16, State::DIELEFT },
        }),
    };
    return QtMocHelpers::metaObjectData<Enemy, qt_meta_tag_ZN5EnemyE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Enemy::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5EnemyE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5EnemyE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5EnemyE_t>.metaTypes,
    nullptr
} };

void Enemy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Enemy *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->positionChanged(); break;
        case 1: _t->visualChanged(); break;
        case 2: _t->stateChanged((*reinterpret_cast< std::add_pointer_t<Enemy::State>>(_a[1]))); break;
        case 3: _t->died(); break;
        case 4: _t->handleAnimationCompleted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Enemy::*)()>(_a, &Enemy::positionChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Enemy::*)()>(_a, &Enemy::visualChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Enemy::*)(Enemy::State )>(_a, &Enemy::stateChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Enemy::*)()>(_a, &Enemy::died, 3))
            return;
    }
}

const QMetaObject *Enemy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Enemy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5EnemyE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Enemy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Enemy::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Enemy::visualChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Enemy::stateChanged(Enemy::State _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Enemy::died()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
