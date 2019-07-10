/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "stdexport.h"
# include <QApplication>
# include <QPixmap>
# include <QMessageBox>

#include "App/DocumentObjectGroup.h"
#include "App/Document.h"

/// Here the FreeCAD includes sorted by Base,App,Gui......
#include "ViewProviderDocumentObjectGroup.h"
#include "Application.h"
#include "Command.h"
#include "BitmapFactory.h"
#include "Document.h"
#include "Tree.h"
#include "View3DInventor.h"
#include "View3DInventorViewer.h"
#include "Base/Console.h"


using namespace Gui;


PROPERTY_SOURCE_WITH_EXTENSIONS(Gui::ViewProviderDocumentObjectGroup, Gui::ViewProviderDocumentObject)


/**
 * Creates the view provider for an object group.
 */
ViewProviderDocumentObjectGroup::ViewProviderDocumentObjectGroup()
{
#if 0
    setDefaultMode(SO_SWITCH_ALL);
#endif
    ViewProviderGroupExtension::initExtension(this);

    sPixmap = "Group.svg";
}

ViewProviderDocumentObjectGroup::~ViewProviderDocumentObjectGroup()
{
}

std::vector<std::string> ViewProviderDocumentObjectGroup::getDisplayModes(void) const
{
    // empty
    return std::vector<std::string>();
}

bool ViewProviderDocumentObjectGroup::isShow(void) const
{
    return Visibility.getValue();
}

/**
 * Extracts the associated view providers of the objects of the associated object group group. 
 */
void ViewProviderDocumentObjectGroup::getViewProviders(std::vector<ViewProviderDocumentObject*>& vp) const
{
    App::DocumentObject* doc = getObject();
    if (doc->getTypeId().isDerivedFrom(App::DocumentObjectGroup::getClassTypeId())) {
        Gui::Document* gd = Application::Instance->getDocument(doc->getDocument());
        App::DocumentObjectGroup* grp = (App::DocumentObjectGroup*)doc;
        std::vector<App::DocumentObject*> obj = grp->getObjects();
        for (std::vector<App::DocumentObject*>::iterator it = obj.begin(); it != obj.end(); ++it) {
            ViewProvider* v = gd->getViewProvider(*it);
            if (v && v->getTypeId().isDerivedFrom(ViewProviderDocumentObject::getClassTypeId()))
                vp.push_back((ViewProviderDocumentObject*)v);
        }
    }
}


// Python feature -----------------------------------------------------------------------

namespace Gui {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Gui::ViewProviderDocumentObjectGroupPython, Gui::ViewProviderDocumentObjectGroup)
/// @endcond

// explicit template instantiation
template class GuiExport ViewProviderPythonFeatureT<ViewProviderDocumentObjectGroup>;
}
