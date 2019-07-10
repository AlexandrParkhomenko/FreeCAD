/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "stdexport.h"
#include "Gui/Control.h"
#include "Gui/BitmapFactory.h"

#include "Mod/Path/App/FeaturePathCompound.h"

#include "TaskDlgPathCompound.h"


using namespace Gui;
using namespace PathGui;

PROPERTY_SOURCE(PathGui::ViewProviderPathCompound, PathGui::ViewProviderPath)


bool ViewProviderPathCompound::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);
    Gui::TaskView::TaskDialog* dlg = new TaskDlgPathCompound(this);
    Gui::Control().showDialog(dlg);
    return true;
}

void ViewProviderPathCompound::unsetEdit(int ModNum)
{
    Q_UNUSED(ModNum);
    // when pressing ESC make sure to close the dialog
    Gui::Control().closeDialog();
}

std::vector<App::DocumentObject*> ViewProviderPathCompound::claimChildren(void)const
{
    return std::vector<App::DocumentObject*>(static_cast<Path::FeatureCompound *>(getObject())->Group.getValues());
}

bool ViewProviderPathCompound::canDragObjects() const
{
    return true;
}

void ViewProviderPathCompound::dragObject(App::DocumentObject* obj)
{
    static_cast<Path::FeatureCompound *>(getObject())->removeObject(obj);
}

bool ViewProviderPathCompound::canDropObjects() const
{
    return true;
}

void ViewProviderPathCompound::dropObject(App::DocumentObject* obj)
{
    static_cast<Path::FeatureCompound *>(getObject())->addObject(obj);
}

QIcon ViewProviderPathCompound::getIcon() const
{
    return Gui::BitmapFactory().pixmap("Path-Compound");
}

// Python object -----------------------------------------------------------------------

namespace Gui {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(PathGui::ViewProviderPathCompoundPython, PathGui::ViewProviderPathCompound)
/// @endcond

// explicit template instantiation
template class PathGuiExport ViewProviderPythonFeatureT<PathGui::ViewProviderPathCompound>;
}
