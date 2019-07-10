/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef SKETCHERGUI_TaskDlgEditSketch_H
#define SKETCHERGUI_TaskDlgEditSketch_H

#include "stdexport.h"
#include "Gui/TaskView/TaskDialog.h"

#include "ViewProviderSketch.h"
#include "TaskSketcherConstrains.h"
#include "TaskSketcherElements.h"
#include "TaskSketcherGeneral.h"
#include "TaskSketcherMessages.h"
#include "TaskSketcherSolverAdvanced.h"
#include <boost/signals2.hpp>

typedef boost::signals2::connection Connection;

namespace SketcherGui {


/// simulation dialog for the TaskView
class SketcherGuiExport TaskDlgEditSketch : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskDlgEditSketch(ViewProviderSketch *sketchView);
    ~TaskDlgEditSketch();
    ViewProviderSketch* getSketchView() const
    { return sketchView; }

public:
    /// is called the TaskView when the dialog is opened
    virtual void open();
    /// is called by the framework if an button is clicked which has no accept or reject role
    virtual void clicked(int);
    /// is called by the framework if the dialog is accepted (Ok)
    virtual bool accept();
    /// is called by the framework if the dialog is rejected (Cancel)
    virtual bool reject();
    virtual bool isAllowedAlterDocument(void) const
    { return false; }

    /// returns for Close and Help button 
    virtual QDialogButtonBox::StandardButtons getStandardButtons(void) const
    { return QDialogButtonBox::Close; }

protected:
    void slotUndoDocument(const App::Document&);
    void slotRedoDocument(const App::Document&);

protected:
    ViewProviderSketch      *sketchView;
    TaskSketcherConstrains  *Constraints;
    TaskSketcherElements    *Elements;
    TaskSketcherGeneral     *General;
    TaskSketcherMessages    *Messages;
    TaskSketcherSolverAdvanced *SolverAdvanced;
    Connection connectUndoDocument;
    Connection connectRedoDocument;
};



} //namespace SketcherGui

#endif // SKETCHERGUI_TaskDlgEditSketch_H
