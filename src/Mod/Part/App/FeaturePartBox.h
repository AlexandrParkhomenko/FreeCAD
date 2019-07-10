/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#ifndef PART_FEATUREPARTBOX_H
#define PART_FEATUREPARTBOX_H

#include "stdexport.h"
#include "App/PropertyStandard.h"

#include "PrimitiveFeature.h"

namespace Part
{

class Standard_EXPORT Box :public Part::Primitive
{
    PROPERTY_HEADER(Part::Box);

public:
    Box();

    App::PropertyLength Length,Height,Width;


    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderBox";
    }
protected:
    void Restore(Base::XMLReader &reader);
    /// get called by the container when a property has changed
    virtual void onChanged (const App::Property* prop);
    //@}
};

} //namespace Part


#endif // PART_FEATUREPARTBOX_H
