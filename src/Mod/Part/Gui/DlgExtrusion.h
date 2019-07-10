/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PARTGUI_DLGEXTRUSION_H
#define PARTGUI_DLGEXTRUSION_H

#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include <string>

#include "Mod/Part/App/FeatureExtrusion.h"

class TopoDS_Shape;

namespace PartGui {

class Ui_DlgExtrusion;
class DlgExtrusion : public QDialog, public Gui::SelectionObserver
{
    Q_OBJECT

public:
    DlgExtrusion(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgExtrusion();
    void accept();
    void apply();
    void reject();

    Base::Vector3d getDir() const;
    void setDir(Base::Vector3d newDir);

    Part::Extrusion::eDirMode getDirMode() const;
    void setDirMode(Part::Extrusion::eDirMode newMode);

    void getAxisLink(App::PropertyLinkSub &lnk) const;
    void setAxisLink(const App::PropertyLinkSub &lnk);
    void setAxisLink(const char* objname, const char* subname);

    std::vector<App::DocumentObject*> getShapesToExtrude() const;

    bool validate();

    void writeParametersToFeature(App::DocumentObject& feature, App::DocumentObject* base) const;

protected:
    void findShapes();
    bool canExtrude(const TopoDS_Shape&) const;
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent*);

private Q_SLOTS:
    void on_rbDirModeCustom_toggled(bool on);
    void on_rbDirModeEdge_toggled(bool on);
    void on_rbDirModeNormal_toggled(bool on);
    void on_btnSelectEdge_clicked();
    void on_btnX_clicked();
    void on_btnY_clicked();
    void on_btnZ_clicked();
    void on_chkSymmetric_toggled(bool on);
    void on_txtLink_textChanged(QString);

private:
    ///updates enabling of controls
    void on_DirMode_changed();
    void onSelectionChanged(const Gui::SelectionChanges& msg);
    ///returns link to any of selected source shapes. Throws if nothing is selected for extrusion.
    App::DocumentObject& getShapeToExtrude() const;
    ///if dirMode is not custom, it tries to compute the actual extrusion direction. Also, it does some auto-magic manipulation of length value.
    void fetchDir();

    ///automatically checks Solid checkbox depending on input shape
    void autoSolid();

private:
    Ui_DlgExtrusion* ui;
    std::string document, label;
    class EdgeSelection;
    EdgeSelection* filter;
};

class TaskExtrusion : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskExtrusion();
    ~TaskExtrusion();

public:
    bool accept();
    bool reject();
    void clicked(int);

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Close; }

private:
    DlgExtrusion* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace PartGui

#endif // PARTGUI_DLGEXTRUSION_H
