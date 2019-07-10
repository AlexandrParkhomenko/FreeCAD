/***************************************************************************
 *   Copyright (c) 2019 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_BREPOFFSETAPI_MAKEOFFSETFIX_H
#define PART_BREPOFFSETAPI_MAKEOFFSETFIX_H

#include "stdexport.h"
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <list>
#include <map>

namespace Part {
/*!
 * \brief The BRepOffsetAPI_MakeOffsetFix class
 * This class works around a limitation of the BRepOffsetAPI_MakeOffset which
 * returns unexpected results when an input wire has set a placement and consists
 * of a single edge only.
 */
class Standard_EXPORT BRepOffsetAPI_MakeOffsetFix : public BRepBuilderAPI_MakeShape
{
public:
    BRepOffsetAPI_MakeOffsetFix();
    BRepOffsetAPI_MakeOffsetFix(const GeomAbs_JoinType Join, const Standard_Boolean IsOpenResult);
    virtual ~BRepOffsetAPI_MakeOffsetFix();

    //! Initializes the algorithm to construct parallels to the wire Spine.
    void AddWire (const TopoDS_Wire& Spine);

    //! Computes a parallel to the spine at distance Offset and
    //! at an altitude Alt from the plane of the spine in relation
    //! to the normal to the spine.
    //! Exceptions: StdFail_NotDone if the offset is not built.
    void Perform (const Standard_Real Offset, const Standard_Real Alt = 0.0);

    //! Builds the resulting shape (redefined from MakeShape).
    void Build();

    virtual Standard_Boolean IsDone() const;

    //! Returns a shape built by the shape construction algorithm.
    //! Raises exception StdFail_NotDone if the shape was not built.
    virtual const TopoDS_Shape& Shape();

    //! returns a list of the created shapes
    //! from the shape <S>.
    virtual const TopTools_ListOfShape& Generated (const TopoDS_Shape& S);

    //! Returns the list  of shapes modified from the shape
    //! <S>.
    virtual const TopTools_ListOfShape& Modified (const TopoDS_Shape& S);

    //! Returns true if the shape S has been deleted.
    virtual Standard_Boolean IsDeleted (const TopoDS_Shape& S);

private:
    void MakeWire(TopoDS_Shape&);

private:
    BRepOffsetAPI_MakeOffset mkOffset;
    std::list<std::pair<TopoDS_Shape, TopLoc_Location> > myLocations;
    TopoDS_Shape myResult;
};

}

#endif // PART_BREPOFFSETAPI_MAKEOFFSETFIX_H
