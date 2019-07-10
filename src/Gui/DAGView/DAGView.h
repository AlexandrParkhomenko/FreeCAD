/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson <blobfish[at]gmx.com>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef DAGVIEW_H
#define DAGVIEW_H

#include <memory>

#include <QGraphicsView>

#include "Gui/DockWindow.h"
#include "Gui/Document.h"
#include "Gui/Selection.h"

#include "DAGModel.h"

namespace Gui
{
  namespace DAG
  {
    //! @brief view for DAG viewer
    class View : public QGraphicsView, public SelectionObserver
    {
      Q_OBJECT
    public:
      View(QWidget *parentIn = 0);
      virtual ~View() override;
      
    public Q_SLOTS:
      void awakeSlot(); //!< hooked up to event dispatcher for update when idle.
      
    private:
      virtual void onSelectionChanged(const SelectionChanges& msg) override;
      
      void slotActiveDocument(const Gui::Document &documentIn);
      void slotDeleteDocument(const Gui::Document &documentIn);
      
      typedef std::map<const Gui::Document*, std::shared_ptr<Model> > ModelMap;
      ModelMap modelMap;
    };
    
    //! @brief dock window for DAG viewer
    class DockWindow : public Gui::DockWindow
    {
        Q_OBJECT
    public:
        DockWindow(Gui::Document* gDocumentIn = 0, QWidget *parent = 0);
        ~DockWindow(){};

    private:
        View *dagView;
    };
  }
}

#endif // DAGVIEW_H
