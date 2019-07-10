/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TREEVIEW_H
#define GUI_TREEVIEW_H

#include "stdexport.h"
#include <QTreeView>

#include "App/Document.h"
#include "App/Application.h"

#include "Gui/DockWindow.h"
#include "Gui/Selection.h"

namespace Gui {

class GuiExport TreeView : public QTreeView
{
    Q_OBJECT
    
public:
    TreeView(QWidget* parent=0);
    virtual ~TreeView();

protected:
    void mouseDoubleClickEvent (QMouseEvent * );
    void rowsInserted (const QModelIndex & parent, int start, int end);
};

}


#endif // GUI_TREEVIEW_H

