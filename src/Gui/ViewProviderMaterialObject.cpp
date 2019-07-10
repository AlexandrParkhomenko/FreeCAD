/***************************************************************************
 *   Copyright (c) 2013 Jürgen Riegel (FreeCAD@juergen-riegel.net)         *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "stdexport.h"
# include <QApplication>
# include <QPixmap>

#include "App/DocumentObjectGroup.h"
#include "App/Document.h"

/// Here the FreeCAD includes sorted by Base,App,Gui......
#include "ViewProviderMaterialObject.h"
#include "Application.h"
#include "Command.h"
#include "BitmapFactory.h"
#include "Document.h"
#include "Tree.h"


using namespace Gui;


PROPERTY_SOURCE(Gui::ViewProviderMaterialObject, Gui::ViewProviderDocumentObject)


/**
 * Creates the view provider for an object group.
 */
ViewProviderMaterialObject::ViewProviderMaterialObject() 
{

}

ViewProviderMaterialObject::~ViewProviderMaterialObject()
{
}

bool ViewProviderMaterialObject::doubleClicked(void)
{
    Gui::Application::Instance->activeDocument()->setEdit(this, (int)ViewProvider::Default);
    return true;
}

/**
 * Returns the pixmap for the list item.
 */
QIcon ViewProviderMaterialObject::getIcon() const
{
    QIcon groupIcon;
    groupIcon.addPixmap(QApplication::style()->standardPixmap(QStyle::SP_DirClosedIcon),
                        QIcon::Normal, QIcon::Off);
    groupIcon.addPixmap(QApplication::style()->standardPixmap(QStyle::SP_DirOpenIcon),
                        QIcon::Normal, QIcon::On);
    return groupIcon;
}


// Python feature -----------------------------------------------------------------------

namespace Gui {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Gui::ViewProviderMaterialObjectPython, Gui::ViewProviderMaterialObject)
/// @endcond

// explicit template instantiation
template class GuiExport ViewProviderPythonFeatureT<ViewProviderMaterialObject>;
}
