/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "stdexport.h"
# include <QApplication>
# include <QMenu>
# include <QPixmap>
# include <boost/bind.hpp>

#include "App/Part.h"
#include "App/Document.h"

#include "ActiveObjectList.h"
#include "ActionFunction.h"
#include "BitmapFactory.h"
#include "Command.h"

#include "ViewProviderPart.h"
#include "Application.h"
#include "MDIView.h"


using namespace Gui;


PROPERTY_SOURCE_WITH_EXTENSIONS(Gui::ViewProviderPart, Gui::ViewProviderDragger)


/**
 * Creates the view provider for an object group.
 */
ViewProviderPart::ViewProviderPart()
{ 
    initExtension(this);

    sPixmap = "Geofeaturegroup.svg";
}

ViewProviderPart::~ViewProviderPart()
{ }

/**
 * TODO
 * Whenever a property of the group gets changed then the same property of all
 * associated view providers of the objects of the object group get changed as well.
 */
void ViewProviderPart::onChanged(const App::Property* prop) {
    ViewProviderDragger::onChanged(prop);
}

void ViewProviderPart::setupContextMenu(QMenu* menu, QObject* receiver, const char* member)
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QObject::tr("Toggle active part"));
    func->trigger(act, boost::bind(&ViewProviderPart::doubleClicked, this));

    ViewProviderDragger::setupContextMenu(menu, receiver, member);
}

bool ViewProviderPart::doubleClicked(void)
{
    //make the part the active one

    //first, check if the part is already active.
    App::DocumentObject* activePart = nullptr;
    MDIView* activeView = this->getActiveView();
    if ( activeView ) {
        activePart = activeView->getActiveObject<App::DocumentObject*> (PARTKEY);
    }

    if (activePart == this->getObject()){
        //active part double-clicked. Deactivate.
        Gui::Command::doCommand(Gui::Command::Gui,
                "Gui.getDocument('%s').ActiveView.setActiveObject('%s', None)",
                this->getObject()->getDocument()->getName(),
                PARTKEY);
    } else {
        //set new active part
        Gui::Command::doCommand(Gui::Command::Gui,
                "Gui.getDocument('%s').ActiveView.setActiveObject('%s', App.getDocument('%s').getObject('%s'))",
                this->getObject()->getDocument()->getName(),
                PARTKEY,
                this->getObject()->getDocument()->getName(),
                this->getObject()->getNameInDocument());
    }

    return true;
}

// Python feature -----------------------------------------------------------------------

namespace Gui {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Gui::ViewProviderPartPython, Gui::ViewProviderPart)
/// @endcond

// explicit template instantiation
template class GuiExport ViewProviderPythonFeatureT<ViewProviderPart>;
}
