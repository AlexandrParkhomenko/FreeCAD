/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef GUI_DOCKWND_SELECTIONVIEW_H
#define GUI_DOCKWND_SELECTIONVIEW_H


#include "DockWindow.h"
#include "Selection.h"

class QListWidget;
class QLabel;

namespace App {
class DocumentObject;
}

namespace Gui {
namespace DockWnd {

/** A test class. A more elaborate class description.
 */
class SelectionView : public Gui::DockWindow, 
                      public Gui::SelectionSingleton::ObserverType
{
    Q_OBJECT

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    SelectionView(Gui::Document* pcDocument, QWidget *parent=0);

    /**
     * A destructor.
     * A more elaborate description of the destructor.
    */
    virtual ~SelectionView();

    /// Observer message from the Selection
    virtual void OnChange(Gui::SelectionSingleton::SubjectType &rCaller,
                          Gui::SelectionSingleton::MessageType Reason);


    bool onMsg(const char* pMsg,const char** ppReturn);

    virtual const char *getName(void) const {return "SelectionView";}

    /// get called when the document is changed or updated
    virtual void onUpdate(void);

    QListWidget* selectionView;
    QLabel*      countLabel;

public Q_SLOTS:
    /// get called when text is entered in the search box
    void search(const QString& text);
    /// get called when enter is pressed in the search box
    void validateSearch(void);
    /// get called when the list is right-clicked
    void onItemContextMenu(const QPoint& point);
    /// different actions
    void select(QListWidgetItem* item=0);
    void deselect(void);
    void zoom(void);
    void treeSelect(void);
    void toPython(void);
    void touch(void);
    void showPart(void);

private:
    QString getModule(const char* type) const;
    QString getProperty(App::DocumentObject* obj) const;
    bool supportPart(App::DocumentObject* obj, const QString& part) const;
    std::vector<App::DocumentObject*> searchList;
};

} // namespace DockWnd
} // namespace Gui

#endif // GUI_DOCKWND_SELECTIONVIEW_H
