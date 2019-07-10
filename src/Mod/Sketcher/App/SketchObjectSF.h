/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2008     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef SKETCH_SKETCHOBJECTSF_H
#define SKETCH_SKETCHOBJECTSF_H

#include "App/PropertyStandard.h"
#include "App/PropertyFile.h"

#include "Mod/Part/App/Part2DObject.h"

namespace Sketcher
{


class SketchObjectSF :public Part::Part2DObject
{
    PROPERTY_HEADER(Sketcher::SketchObjectSF);

public:
    SketchObjectSF();

    /// Property
    App::PropertyFileIncluded SketchFlatFile;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// Uses the standard ViewProvider
    //const char* getViewProviderName(void) const {
    //    return "SketcherGui::ViewProviderSketchSF";
    //}
    //@}

    bool save(const char* FileName);
    bool load(const char* FileName);


};

} //namespace Part


#endif // SKETCH_SKETCHOBJECTSF_H
