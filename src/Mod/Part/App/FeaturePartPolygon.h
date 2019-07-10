/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATUREPARTPOLYGON_H
#define PART_FEATUREPARTPOLYGON_H

#include "App/PropertyGeo.h"

#include "PartFeature.h"

namespace Part
{

class Polygon : public Part::Feature
{
    PROPERTY_HEADER(Part::Polygon);

public:
    Polygon();
    virtual ~Polygon();

    App::PropertyVectorList Nodes;
    App::PropertyBool       Close;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    //@}
};

} //namespace Part

#endif // PART_FEATUREPARTPOLYGON_H
