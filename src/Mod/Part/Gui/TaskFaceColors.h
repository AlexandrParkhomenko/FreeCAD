/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_TASKSETCOLORS_H
#define PARTGUI_TASKSETCOLORS_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/TaskView/TaskDialog.h"

namespace Gui {
    class Document;
    class ViewProvider;
}

namespace PartGui { 

class ViewProviderPartExt;

class FaceColors : public QWidget, public Gui::SelectionObserver
{
    Q_OBJECT

public:
    FaceColors(ViewProviderPartExt* vp, QWidget* parent = 0);
    ~FaceColors();

    bool accept();
    bool reject();

private Q_SLOTS:
    void on_colorButton_changed();
    void on_defaultButton_clicked();
    void on_boxSelection_clicked();

protected:
    void onSelectionChanged(const Gui::SelectionChanges& msg);
    void changeEvent(QEvent *e);
    void slotDeleteDocument(const Gui::Document&);
    void slotDeleteObject(const Gui::ViewProvider&);
    void updatePanel();

private:
    class Private;
    Private* d;
};

class TaskFaceColors : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskFaceColors(ViewProviderPartExt* vp);
    ~TaskFaceColors();

public:
    void open();
    bool accept();
    bool reject();
    void clicked(int);

    QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }

private:
    FaceColors* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace PartGui

#endif // PARTGUI_TASKSETCOLORS_H
