/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <boost/bind.hpp>

#include "TaskDlgEditSketch.h"
#include "ViewProviderSketch.h"
#include "Gui/Command.h"

using namespace SketcherGui;


//**************************************************************************
//**************************************************************************
// TaskDialog
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskDlgEditSketch::TaskDlgEditSketch(ViewProviderSketch *sketchView)
    : TaskDialog(),sketchView(sketchView)
{
    assert(sketchView);
    Constraints = new TaskSketcherConstrains(sketchView);
    Elements = new TaskSketcherElements(sketchView);
    General = new TaskSketcherGeneral(sketchView);
    Messages = new TaskSketcherMessages(sketchView);
    SolverAdvanced = new TaskSketcherSolverAdvanced(sketchView);

    ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/Sketcher");

    Content.push_back(Messages);

    if (hGrp->GetBool("ShowSolverAdvancedWidget",false)) {
        Content.push_back(SolverAdvanced);
    }

    Content.push_back(General);
    Content.push_back(Constraints);
    Content.push_back(Elements);

    if (!hGrp->GetBool("ExpandedMessagesWidget",true))
        Messages->hideGroupBox();
    if (!hGrp->GetBool("ExpandedSolverAdvancedWidget",false))
        SolverAdvanced->hideGroupBox();
    if (!hGrp->GetBool("ExpandedEditControlWidget",false))
        General->hideGroupBox();
    if (!hGrp->GetBool("ExpandedConstraintsWidget",true))
        Constraints->hideGroupBox();
    if (!hGrp->GetBool("ExpandedElementsWidget",true))
        Elements->hideGroupBox();

    App::Document* document = sketchView->getObject()->getDocument();
    connectUndoDocument =
        document->signalUndo.connect(boost::bind(&TaskDlgEditSketch::slotUndoDocument, this, _1));
    connectRedoDocument =
        document->signalRedo.connect(boost::bind(&TaskDlgEditSketch::slotRedoDocument, this, _1));
}

TaskDlgEditSketch::~TaskDlgEditSketch()
{
    connectUndoDocument.disconnect();
    connectRedoDocument.disconnect();

    // to make sure to delete the advanced solver panel
    // it must be part to the 'Content' array
    std::vector<QWidget*>::iterator it = std::find(Content.begin(), Content.end(), SolverAdvanced);
    if (it == Content.end())
        Content.push_back(SolverAdvanced);
}

void TaskDlgEditSketch::slotUndoDocument(const App::Document& doc)
{
    const_cast<App::Document&>(doc).recomputeFeature(sketchView->getObject());
}

void TaskDlgEditSketch::slotRedoDocument(const App::Document& doc)
{
    const_cast<App::Document&>(doc).recomputeFeature(sketchView->getObject());
}

//==== calls from the TaskView ===============================================================


void TaskDlgEditSketch::open()
{

}

void TaskDlgEditSketch::clicked(int)
{

}

bool TaskDlgEditSketch::accept()
{
    return true;
}

bool TaskDlgEditSketch::reject()
{
    ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/Sketcher");
    hGrp->SetBool("ExpandedMessagesWidget",Messages->isGroupVisible());
    hGrp->SetBool("ExpandedSolverAdvancedWidget",SolverAdvanced->isGroupVisible());
    hGrp->SetBool("ExpandedEditControlWidget",General->isGroupVisible());
    hGrp->SetBool("ExpandedConstraintsWidget",Constraints->isGroupVisible());
    hGrp->SetBool("ExpandedElementsWidget",Elements->isGroupVisible());
    
    std::string document = getDocumentName(); // needed because resetEdit() deletes this instance
    Gui::Command::doCommand(Gui::Command::Gui,"Gui.getDocument('%s').resetEdit()", document.c_str());
    Gui::Command::doCommand(Gui::Command::Doc,"App.getDocument('%s').recompute()", document.c_str());

    return true;
}


#include "moc_TaskDlgEditSketch.cpp"
