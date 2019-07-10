/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_DLGREGULARSOLID_IMP_H
#define MESHGUI_DLGREGULARSOLID_IMP_H

#include "ui_DlgRegularSolid.h"

namespace MeshGui {
class DlgRegularSolidImp : public QDialog, public Ui_DlgRegularSolid
{
    Q_OBJECT

public:
    DlgRegularSolidImp(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgRegularSolidImp();

public Q_SLOTS:
    void on_createSolidButton_clicked();

protected:
    void changeEvent(QEvent *e);
};

/**
 * The SingleDlgRegularSolidImp class creates a single instance.
 * \author Werner Mayer
 */
class SingleDlgRegularSolidImp : public DlgRegularSolidImp
{ 
protected:
    SingleDlgRegularSolidImp(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~SingleDlgRegularSolidImp();

public:
    static SingleDlgRegularSolidImp* instance();
    static void destruct();
    static bool hasInstance();

private:
    static SingleDlgRegularSolidImp* _instance;
};

}

#endif // MESHGUI_DLGREGULARSOLID_IMP_H
