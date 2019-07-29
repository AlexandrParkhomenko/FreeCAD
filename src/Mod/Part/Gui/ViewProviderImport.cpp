/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ViewProviderImport.h"
#include "Mod/Part/App/PartFeature.h"

#include "Base/Console.h"
#include "Base/Parameter.h"
#include "Base/Exception.h"
#include "Base/Sequencer.h"
#include "Gui/View3DInventorViewer.h"
#include "App/Application.h"


using namespace PartGui;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderImport,PartGui::ViewProviderPart)

ViewProviderImport::ViewProviderImport()
{
    sPixmap = "PartFeatureImport";
}

ViewProviderImport::~ViewProviderImport()
{

}

// **********************************************************************************

bool ViewProviderImport::setEdit(int ModNum)
{
    return ViewProviderPart::setEdit(ModNum);
}

void ViewProviderImport::unsetEdit(int ModNum)
{
    ViewProviderPart::unsetEdit(ModNum);
}
