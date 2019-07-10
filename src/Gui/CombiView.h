/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef GUI_DOCKWND_COMBIVIEW_H
#define GUI_DOCKWND_COMBIVIEW_H

#include "stdexport.h"
#include "DockWindow.h"
#include "Selection.h"

class QTabWidget;
class QTreeView;

namespace App {
  class PropertyContainer;
}

namespace Gui {
    class TreeWidget;
    class PropertyView;
    class ProjectWidget;
    class TreePanel;
namespace PropertyEditor {
class EditableListView;
class EditableItem;
class PropertyEditor;
} // namespace PropertyEditor

namespace TaskView {
class TaskView;
class TaskDialog;
} // namespace TaskView
} // namespace Gui


namespace Gui {
    class ControlSingleton;
namespace DockWnd {

/** Combi View
  * is a combination of a tree, property and TaskPanel for 
  * integrated user action.
 */
class GuiExport CombiView : public Gui::DockWindow
{
    Q_OBJECT

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    CombiView(Gui::Document*  pcDocument, QWidget *parent=0);

    /**
     * A destructor.
     * A more elaborate description of the destructor.
    */
    virtual ~CombiView();

    Gui::TaskView::TaskView *getTaskPanel(void){return taskPanel;}
    QTabWidget* getTabPanel() const { return tabs;}


    friend class Gui::ControlSingleton;

    void showTreeView();
    void showTaskView();

protected:
    void showDialog(Gui::TaskView::TaskDialog *dlg);
    void closeDialog();
    void closedDialog();
    void changeEvent(QEvent *e);

    int oldTabIndex;

private:
    QTabWidget                         * tabs;
    Gui::PropertyView                  * prop;
    Gui::TreePanel                     * tree;
    Gui::TaskView::TaskView            * taskPanel;
  //Gui::ProjectWidget                 * projectView;
};

} // namespace DockWnd
} // namespace Gui

#endif // GUI_DOCKWND_SELECTIONVIEW_H
