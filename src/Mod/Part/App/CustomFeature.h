/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_CUSTOMFEATURE_H
#define PART_CUSTOMFEATURE_H

#include "stdexport.h"
#include "Mod/Part/App/PartFeature.h"

namespace Part
{

/** Base class of all custom feature classes which are almost used as base
 * for python feature classes.
 */
class Standard_EXPORT CustomFeature : public Part::Feature
{
    PROPERTY_HEADER(Part::UserFeature);

public:
    /// Constructor
    CustomFeature(void);
    virtual ~CustomFeature();

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute(void);
    virtual short mustExecute(void) const;
    //@}

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderCustom";
    }
};

typedef App::FeaturePythonT<CustomFeature> CustomFeaturePython;

} //namespace Part


#endif // PART_CUSTOMFEATURE_H
