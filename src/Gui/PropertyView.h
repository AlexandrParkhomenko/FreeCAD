/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef GUI_DOCKWND_PROPERTYVIEW_H
#define GUI_DOCKWND_PROPERTYVIEW_H


#include "DockWindow.h"
#include "Selection.h"
#include <boost/signals2.hpp>

class QPixmap;
class QTabWidget;

namespace App {
  class Property;
  class PropertyContainer;
  class DocumentObject;
}

namespace Gui {
namespace PropertyEditor {

class EditableListView;
class EditableItem;
class PropertyEditor;

} // namespace PropertyEditor
} // namespace Gui

namespace Gui {
class ViewProvider;

/** The property view class.
 */
class PropertyView : public QWidget, public Gui::SelectionObserver
{
    Q_OBJECT

public:
    PropertyView(QWidget *parent=0);
    virtual ~PropertyView();

    Gui::PropertyEditor::PropertyEditor* propertyEditorView;
    Gui::PropertyEditor::PropertyEditor* propertyEditorData;

public Q_SLOTS:
    /// Stores a preference for the last tab selected
    void tabChanged(int index);

protected:
    void changeEvent(QEvent *e);

private:
    void onSelectionChanged(const SelectionChanges& msg);
    void slotChangePropertyData(const App::DocumentObject&, const App::Property&);
    void slotChangePropertyView(const Gui::ViewProvider&, const App::Property&);
    void slotAppendDynamicProperty(const App::Property&);
    void slotRemoveDynamicProperty(const App::Property&);
    void slotChangePropertyEditor(const App::Property&);
    void slotActiveDocument(const Gui::Document&);

private:
    struct PropInfo;
    struct PropFind;
    typedef boost::signals2::connection Connection;
    Connection connectPropData;
    Connection connectPropView;
    Connection connectPropAppend;
    Connection connectPropRemove;
    Connection connectPropChange;
    Connection connectActiveDoc;
    QTabWidget* tabs;
};

namespace DockWnd {

/** A dock window with the embedded property view.
 */
class PropertyDockView : public Gui::DockWindow
{
    Q_OBJECT

public:
    PropertyDockView(Gui::Document*  pcDocument, QWidget *parent=0);
    virtual ~PropertyDockView();
};

} // namespace DockWnd
} // namespace Gui

#endif // GUI_DOCKWND_PROPERTYVIEW_H
