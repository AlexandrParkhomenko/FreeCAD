/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC)      <vv.titov@gmail.com>  *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PART_FACEMAKER_BULLSEYE_H
#define PART_FACEMAKER_BULLSEYE_H

#include "stdexport.h"
#include "FaceMaker.h"
#include <list>

#include <Geom_Surface.hxx>
#include <gp_Pln.hxx>

namespace Part
{


/**
 * @brief The FaceMakerBullseye class is a tool to make planar faces with holes,
 * where there can be additional faces inside holes and they can have holes too
 * and so on.
 *
 * Strengths: makes faces with holes with islands
 *
 * Weaknesses: faces of one compound must be on same plane. TBD
 */
class Standard_EXPORT FaceMakerBullseye: public FaceMakerPublic
{
    TYPESYSTEM_HEADER_WITH_OVERRIDE();
public:
    FaceMakerBullseye()
        :planeSupplied(false){}
    /**
     * @brief setPlane: sets the plane to use when making faces. This is
     * optional. If the plane was set, it is not tested that the wires are
     * planar or on the supplied plane, potentially speeding things up.
     * @param plane FIXME: the plane is not propagated if processing compounds.
     */
    void setPlane(const gp_Pln& plane);

    virtual std::string getUserFriendlyName() const override;
    virtual std::string getBriefExplanation() const override;

protected:
    virtual void Build_Essence() override;

protected:
    gp_Pln myPlane; //externally supplied plane (if any)
    bool planeSupplied;

    /**
     * @brief The FaceDriller class is similar to BRepBuilderAPI_MakeFace,
     * except that it is tolerant to wire orientation (wires are oriented as
     * needed automatically).
     */
    class FaceDriller
    {
    public:
        FaceDriller(gp_Pln plane, TopoDS_Wire outerWire);

        /**
         * @brief hitTest: returns True if point is on the face
         * @param point
         */
        bool hitTest(gp_Pnt point) const;

        void addHole(TopoDS_Wire w);

        TopoDS_Face Face() {return myFace;}
    public:
        /**
         * @brief wireDirection: determines direction of wire with respect to
         * myPlane.
         * @param w
         * @return  1 = CCW (suits as outer wire), -1 = CW (suits as hole)
         */
        static int getWireDirection(const gp_Pln &plane, const TopoDS_Wire &w);
    private:
        gp_Pln myPlane;
        TopoDS_Face myFace;
        Handle(Geom_Surface) myHPlane;
    };
};


}//namespace Part
#endif // PART_FACEMAKER_BULLSEYE_H
