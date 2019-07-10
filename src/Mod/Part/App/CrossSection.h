/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_CROSSSECTION_H
#define PART_CROSSSECTION_H

#include "stdexport.h"
#include <list>
#include <TopTools_IndexedMapOfShape.hxx>

class TopoDS_Shape;
class TopoDS_Wire;

namespace Part {

class Standard_EXPORT CrossSection
{
public:
    CrossSection(double a, double b, double c, const TopoDS_Shape& s);
    std::list<TopoDS_Wire> slice(double d) const;

private:
    void sliceNonSolid(double d, const TopoDS_Shape&, std::list<TopoDS_Wire>& wires) const;
    void sliceSolid(double d, const TopoDS_Shape&, std::list<TopoDS_Wire>& wires) const;
    void connectEdges (const std::list<TopoDS_Edge>& edges, std::list<TopoDS_Wire>& wires) const;
    void connectWires (const TopTools_IndexedMapOfShape& wireMap, std::list<TopoDS_Wire>& wires) const;

private:
    double a,b,c;
    const TopoDS_Shape& s;
};

}

#endif // PART_CROSSSECTION_H
