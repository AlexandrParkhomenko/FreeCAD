/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "ProgressIndicator.h"

using namespace Part;
/*!
  \code
  #include <XSControl_WorkSession.hxx>
  #include <Transfer_TransientProcess.hxx>

  STEPControl_Reader aReader;
  Handle(Message_ProgressIndicator) pi = new ProgressIndicator(100);

  pi->NewScope(20, "Loading STEP file...");
  pi->Show();
  aReader.ReadFile("myfile.stp");
  pi->EndScope();

  Handle(StepData_StepModel) Model = aReader.StepModel();
  pi->NewScope(80, "Translating...");
  pi->Show();
  aReader.WS()->MapReader()->SetProgress(pi);
  Standard_Integer nbr = aReader.NbRootsForTransfer();
  for ( Standard_Integer n = 1; n<= nbr; n++) {
    ...
  }

  pi->EndScope();
  \endcode
 */

ProgressIndicator::ProgressIndicator (int theMaxVal)
  : myProgress(new Base::SequencerLauncher("", theMaxVal))
{
    SetScale (0, theMaxVal, 1);
}

ProgressIndicator::~ProgressIndicator ()
{
}

Standard_Boolean ProgressIndicator::Show (const Standard_Boolean theForce)
{
    if (theForce) {
        Handle(TCollection_HAsciiString) aName = GetScope(1).GetName(); //current step
        if (!aName.IsNull())
            myProgress->setText (aName->ToCString());
    }

    Standard_Real aPc = GetPosition(); //always within [0,1]
    int aVal = (int)(aPc * myProgress->numberOfSteps());
    myProgress->setProgress (aVal);

    return Standard_True;
}

Standard_Boolean ProgressIndicator::UserBreak()
{
    return myProgress->wasCanceled();
}
