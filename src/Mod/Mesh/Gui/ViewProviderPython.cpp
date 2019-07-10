/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "stdexport.h"
#include "ViewProviderPython.h"

namespace Gui {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(MeshGui::ViewProviderPython, MeshGui::ViewProviderMeshFaceSet)
/// @endcond

// explicit template instantiation
template class MeshGuiExport ViewProviderPythonFeatureT<MeshGui::ViewProviderMeshFaceSet>;
}

