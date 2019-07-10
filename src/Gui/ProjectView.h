/***************************************************************************
 *   Copyright (c) 2012 Juergen Riegel <juergen.riegel@web.de>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_ProjectView_H
#define GUI_ProjectView_H

#include <QTreeView>

#include "App/Document.h"
#include "App/Application.h"

#include "Gui/DockWindow.h"
#include "Gui/Selection.h"
class QDirModel;

namespace Gui {


/** Tree view that allows drag & drop of document objects.
 * @author Werner Mayer
 */
class ProjectWidget : public QTreeView
{
    Q_OBJECT

public:
    ProjectWidget(QWidget* parent=0);
    ~ProjectWidget();

private:
    QDirModel *fileModel;
 
};



}


#endif // GUI_ProjectView_H

