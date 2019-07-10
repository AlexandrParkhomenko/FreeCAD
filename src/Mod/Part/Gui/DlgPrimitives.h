/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PARTGUI_DLGPRIMITIVES_H
#define PARTGUI_DLGPRIMITIVES_H

#include <QEventLoop>
#include <QPointer>
#include "Gui/TaskView/TaskDialog.h"
#include "Mod/Part/Gui/ui_DlgPrimitives.h"
#include "Mod/Part/Gui/ui_Location.h"

class gp_Ax2;
class SoEventCallback;

namespace App { class Document; }
namespace Gui { class Document; }
namespace PartGui {

class Picker
{
public:
    Picker() : exitCode(-1)
    {
    }
    virtual ~Picker()
    {
    }

    virtual bool pickedPoint(const SoPickedPoint * point) = 0;
    virtual QString command(App::Document*) const = 0;
    void createPrimitive(QWidget* widget, const QString&, Gui::Document*);
    QString toPlacement(const gp_Ax2&) const;

    int exitCode;
    QEventLoop loop;
};

class DlgPrimitives : public QWidget
{
    Q_OBJECT

public:
    DlgPrimitives(QWidget* parent = 0);
    ~DlgPrimitives();
    void createPrimitive(const QString&);

private Q_SLOTS:
    void on_buttonCircleFromThreePoints_clicked();

private:
    static void pickCallback(void * ud, SoEventCallback * n);
    void executeCallback(Picker*);

private:
    Ui_DlgPrimitives ui;
};

class Location : public QWidget
{
    Q_OBJECT

public:
    Location(QWidget* parent = 0);
    ~Location();
    QString toPlacement() const;

private Q_SLOTS:
    void on_viewPositionButton_clicked();

private:
    static void pickCallback(void * ud, SoEventCallback * n);
    int mode;
    QPointer<QWidget> activeView;
    Ui_Location ui;
};

class TaskPrimitives : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskPrimitives();
    ~TaskPrimitives();

public:
    bool accept();
    bool reject();

    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private:
    DlgPrimitives* widget;
    Location* location;
};

} // namespace PartGui

#endif // PARTGUI_DLGPRIMITIVES_H
