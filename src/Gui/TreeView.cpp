/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <QMouseEvent>

#include "TreeView.h"
#include "DocumentModel.h"
#include "Application.h"
#include "Document.h"
#include "MDIView.h"
#include "MainWindow.h"
#include "ViewProvider.h"

using namespace Gui;

TreeView::TreeView(QWidget* parent)
  : QTreeView(parent)
{
    setModel(new DocumentModel(this));
    QModelIndex root = this->model()->index(0,0,QModelIndex());
    this->setExpanded(root, true);
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(false);
    this->setRootIsDecorated(false);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setMouseTracking(true); // needed for itemEntered() to work
}

TreeView::~TreeView()
{
}

void TreeView::mouseDoubleClickEvent (QMouseEvent * event)
{
    QModelIndex index = indexAt(event->pos());
    if (!index.isValid() || index.internalPointer() == Application::Instance)
        return;
    Base::BaseClass* item = 0;
    item = static_cast<Base::BaseClass*>(index.internalPointer());
    if (item->getTypeId() == Document::getClassTypeId()) {
        QTreeView::mouseDoubleClickEvent(event);
        const Gui::Document* doc = static_cast<Gui::Document*>(item);
        MDIView *view = doc->getActiveView();
        if (!view) return;
        getMainWindow()->setActiveWindow(view);
    }
    else if (item->getTypeId().isDerivedFrom(ViewProvider::getClassTypeId())) {
        if (static_cast<ViewProvider*>(item)->doubleClicked() == false)
            QTreeView::mouseDoubleClickEvent(event);
    }
}

void TreeView::rowsInserted (const QModelIndex & parent, int start, int end)
{
    QTreeView::rowsInserted(parent, start, end);
    if (parent.isValid()) {
        Base::BaseClass* ptr = static_cast<Base::BaseClass*>(parent.internalPointer());
        // type is defined in DocumentModel.cpp
        if (ptr->getTypeId() == Base::Type::fromName("Gui::ApplicationIndex")) {
            for (int i=start; i<=end;i++) {
                QModelIndex document = this->model()->index(i, 0, parent);
                this->expand(document);
            }
        }
    }
}

#include "moc_TreeView.cpp"

