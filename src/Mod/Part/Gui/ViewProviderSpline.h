/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#ifndef PARTGUI_VIEWPROVIDERPARTSPLINE_H
#define PARTGUI_VIEWPROVIDERPARTSPLINE_H

#include "stdexport.h"
#include "ViewProviderExt.h"

namespace PartGui
{

class PartGuiExport ViewProviderSpline : public ViewProviderPartExt
{
    PROPERTY_HEADER(PartGui::ViewProviderSpline);

public:
    /// constructor
    ViewProviderSpline();
    /// destructor
    virtual ~ViewProviderSpline();

    // Display properties
    App::PropertyBool ControlPoints;

    void updateData(const App::Property* prop);
    void setupContextMenu(QMenu* menu, QObject* receiver, const char* member);

protected:
    void onChanged(const App::Property* prop);
    void toggleControlPoints(bool);
    void showControlPoints(bool, const App::Property* prop);
    void showControlPointsOfEdge(const TopoDS_Edge&);
    void showControlPointsOfFace(const TopoDS_Face&);

    SoSwitch     *pcControlPoints;
};

} //namespace PartGui


#endif // PARTGUI_VIEWPROVIDERPARTSPLINE_H

