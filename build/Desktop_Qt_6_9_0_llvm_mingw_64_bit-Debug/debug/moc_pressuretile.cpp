/****************************************************************************
** Meta object code from reading C++ file 'pressuretile.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../Downloads/prince_enemy(obstacle1)/prince_enemy/pressuretile.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pressuretile.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12PressureTileE_t {};
} // unnamed namespace

template <> constexpr inline auto PressureTile::qt_create_metaobjectdata<qt_meta_tag_ZN12PressureTileE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PressureTile",
        "playeronTile",
        "",
        "playerLeaveTile"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'playeronTile'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playerLeaveTile'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PressureTile, qt_meta_tag_ZN12PressureTileE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PressureTile::staticMetaObject = { {
    QMetaObject::SuperData::link<Obstacle::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12PressureTileE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12PressureTileE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12PressureTileE_t>.metaTypes,
    nullptr
} };

void PressureTile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PressureTile *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->playeronTile(); break;
        case 1: _t->playerLeaveTile(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PressureTile::*)()>(_a, &PressureTile::playeronTile, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PressureTile::*)()>(_a, &PressureTile::playerLeaveTile, 1))
            return;
    }
}

const QMetaObject *PressureTile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PressureTile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12PressureTileE_t>.strings))
        return static_cast<void*>(this);
    return Obstacle::qt_metacast(_clname);
}

int PressureTile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obstacle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PressureTile::playeronTile()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PressureTile::playerLeaveTile()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
