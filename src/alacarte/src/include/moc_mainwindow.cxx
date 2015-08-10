/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      20,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      46,   11,   11,   11, 0x08,
      61,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
      92,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     128,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     144,   11,   11,   11, 0x08,
     152,   11,   11,   11, 0x08,
     165,   11,   11,   11, 0x08,
     177,   11,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,
     217,  215,   11,   11, 0x08,
     236,   11,   11,   11, 0x08,
     249,   11,   11,   11, 0x08,
     262,   11,   11,   11, 0x08,
     284,  282,   11,   11, 0x08,
     306,   11,   11,   11, 0x08,
     322,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0about()\0loadRecipe()\0"
    "saveRecipe()\0saveAsRecipe()\0recipeChanged()\0"
    "updateFilter()\0set()\0clear()\0exporttable()\0"
    "setLD()\0setDD()\0setCH()\0setGP()\0"
    "addchannel()\0rmchannel()\0updatechannel()\0"
    "updateChannelFilter()\0i\0channelchange(int)\0"
    "exportList()\0exportMake()\0loadTemplateNames()\0"
    "n\0loadTemplate(QString)\0writeTemplate()\0"
    "deleteTemplate()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->about(); break;
        case 1: _t->loadRecipe(); break;
        case 2: _t->saveRecipe(); break;
        case 3: _t->saveAsRecipe(); break;
        case 4: _t->recipeChanged(); break;
        case 5: _t->updateFilter(); break;
        case 6: _t->set(); break;
        case 7: _t->clear(); break;
        case 8: _t->exporttable(); break;
        case 9: _t->setLD(); break;
        case 10: _t->setDD(); break;
        case 11: _t->setCH(); break;
        case 12: _t->setGP(); break;
        case 13: _t->addchannel(); break;
        case 14: _t->rmchannel(); break;
        case 15: _t->updatechannel(); break;
        case 16: _t->updateChannelFilter(); break;
        case 17: _t->channelchange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->exportList(); break;
        case 19: _t->exportMake(); break;
        case 20: _t->loadTemplateNames(); break;
        case 21: _t->loadTemplate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->writeTemplate(); break;
        case 23: _t->deleteTemplate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
