/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC)      <vv.titov@gmail.com>  *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PART_FACEMAKER_CHEESE_H
#define PART_FACEMAKER_CHEESE_H

#include "stdexport.h"
#include "FaceMaker.h"
#include <list>
#include <functional>

namespace Part
{


/**
 * @brief The FaceMakerCheese class is a legacy face maker that was extracted
 * from Part Extrude. It is used by almost all PartDesign.
 *
 * Strengths: makes faces with holes
 *
 * Weaknesses: can't make islands in holes. All faces must be on same plane.
 */
class Standard_EXPORT FaceMakerCheese: public FaceMakerPublic
{
    TYPESYSTEM_HEADER_WITH_OVERRIDE();
public:
    virtual std::string getUserFriendlyName() const override;
    virtual std::string getBriefExplanation() const override;

public: //in Extrusion, they used to be private. but they are also used by PartDesign, so made public.
    /**
     * @brief The Wire_Compare class is for sorting wires by bounding box diagonal length
     */
    class Wire_Compare : public std::binary_function<const TopoDS_Wire&,
            const TopoDS_Wire&, bool>
    {
    public:
        bool operator() (const TopoDS_Wire& w1, const TopoDS_Wire& w2);
    };

    static TopoDS_Shape makeFace(const std::vector<TopoDS_Wire>&);
    static TopoDS_Face validateFace(const TopoDS_Face&);
    static bool isInside(const TopoDS_Wire&, const TopoDS_Wire&);

private:
    static TopoDS_Shape makeFace(std::list<TopoDS_Wire>&); // for internal use only

protected:
    virtual void Build_Essence() override;
};


}//namespace Part
#endif // PART_FACEMAKER_CHEESE_H
