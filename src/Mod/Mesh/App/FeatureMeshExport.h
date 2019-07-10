/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_FEATUREMESHEXPORT_H
#define MESH_FEATUREMESHEXPORT_H

#include "stdexport.h"
#include "App/DocumentObject.h"
#include "App/PropertyStandard.h"
#include "App/PropertyLinks.h"

namespace Mesh
{

/**
 * The Export class writes any supported mesh format into a file.
 * @author Werner Mayer
 */
class Standard_EXPORT Export : public App::DocumentObject
{
    PROPERTY_HEADER(Mesh::Export);

public:
    Export();

    App::PropertyLink   Source;
    App::PropertyString FileName;
    App::PropertyString Format;
    const char* getViewProviderName(void) const {
        return "MeshGui::ViewProviderExport";
    }

    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    //@}
};

}

#endif // MESH_FEATUREMESHEXPORT_H 
