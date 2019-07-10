/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATUREPARTCIRCLE_H
#define PART_FEATUREPARTCIRCLE_H

#include "App/PropertyUnits.h"
#include "PrimitiveFeature.h"

namespace Part
{
class Circle : public Part::Primitive
{
    PROPERTY_HEADER(Part::Circle);

public:
    Circle();
    virtual ~Circle();

    App::PropertyLength Radius;
    App::PropertyAngle Angle0;
    App::PropertyAngle Angle1;

    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    void onChanged(const App::Property*);
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderCircleParametric";
    }

private:
    static App::PropertyQuantityConstraint::Constraints angleRange;
    //@}
};

} //namespace Part

#endif // PART_FEATUREPARTCIRCLE_H
