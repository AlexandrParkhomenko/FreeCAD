/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESHGUI_VIEWPROVIDERPYTHON_H
#define MESHGUI_VIEWPROVIDERPYTHON_H

#include "Gui/ViewProviderPythonFeature.h"
#include "Mod/Mesh/Gui/ViewProviderMeshFaceSet.h"

namespace MeshGui {

typedef Gui::ViewProviderPythonFeatureT<ViewProviderMeshFaceSet> ViewProviderPython;

} // namespace MeshGui


#endif // MESHGUI_VIEWPROVIDERPYTHON_H

