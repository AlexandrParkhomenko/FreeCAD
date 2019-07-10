/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATUREMIRRORING_H
#define PART_FEATUREMIRRORING_H

#include "App/PropertyStandard.h"
#include "PartFeature.h"
#include "Base/Matrix.h"

namespace Part
{

class Mirroring : public Part::Feature
{
    PROPERTY_HEADER(Part::Mirroring);

public:
    Mirroring();

    App::PropertyLink Source;
    App::PropertyPosition Base;
    App::PropertyDirection Normal;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderMirror";
    }
    //@}

protected:
    void onChanged (const App::Property* prop);

    void handleChangedPropertyType(Base::XMLReader &reader, const char *TypeName, App::Property * prop);

};

} //namespace Part


#endif // PART_FEATUREMIRRORING_H
