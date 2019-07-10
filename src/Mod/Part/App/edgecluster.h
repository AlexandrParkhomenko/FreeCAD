/***************************************************************************
 *   Copyright (c) 2007                                                    *
 *   Joachim Zettler <Joachim.Zettler@gmx.de>                              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_EDGECLUSTER_H
#define PART_EDGECLUSTER_H

#include "stdexport.h"
#include <gp_Pnt.hxx>
#include <TopoDS_Edge.hxx>
#include <vector>
#include <map>


namespace Part {

struct Edgesort_gp_Pnt_Less
{
    bool operator()(const gp_Pnt & _Left, const gp_Pnt & _Right) const
    {
        Standard_Real x1,y1,z1,x2,y2,z2;
        _Left.Coord(x1,y1,z1);
        _Right.Coord(x2,y2,z2);
        if ( fabs(x1- x2) > 0.2 )
            return x1 < x2;
        else if ( fabs(y1 -y2) > 0.2 )
            return y1 < y2;
        else if ( fabs(z1 -z2) > 0.2 )
            return z1 < z2;
        return false;
    }
};


typedef std::vector<TopoDS_Edge> tEdgeVector;
typedef std::map<gp_Pnt,tEdgeVector,Edgesort_gp_Pnt_Less>  tMapPntEdge;
typedef std::pair<gp_Pnt,tEdgeVector> tMapPntEdgePair;
typedef std::vector<std::vector<TopoDS_Edge> > tEdgeClusterVector;


class Standard_EXPORT Edgecluster
{
public:
    Edgecluster(const std::vector<TopoDS_Edge>& usorted_edges);
    virtual ~Edgecluster(void);

    tEdgeClusterVector GetClusters(void);

private:
    void Perform();
    void Perform(const TopoDS_Edge& edge);
    bool PerformEdges(gp_Pnt& point);
    bool IsValidEdge(const TopoDS_Edge& edge);

    tEdgeClusterVector m_final_cluster;
    tEdgeVector m_unsortededges;
    tEdgeVector m_edges;

    tMapPntEdge m_vertices;
    bool m_done;

    tEdgeVector::const_iterator m_edgeIter;

};

}

#endif // PART_EDGECLUSTER_H
