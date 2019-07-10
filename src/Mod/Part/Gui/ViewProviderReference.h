/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_ViewProviderPartReference_H
#define PARTGUI_ViewProviderPartReference_H

#include "stdexport.h"
#include <Standard_math.hxx>
#include <Standard_Boolean.hxx>
#include <TopoDS_Shape.hxx>
#include "Gui/ViewProviderGeometryObject.h"
#include "Gui/ViewProviderBuilder.h"
#include <map>

class TopoDS_Shape;
class TopoDS_Edge;
class TopoDS_Wire;
class TopoDS_Face;
class SoSeparator;
class SoGroup;
class SoSwitch;
class SoVertexShape;
class SoPickedPoint;
class SoShapeHints;
class SoEventCallback;
class SbVec3f;
class SoSphere;
class SoScale;

namespace PartGui {


class PartGuiExport ViewProviderPartReference : public Gui::ViewProviderGeometryObject
{
    PROPERTY_HEADER(PartGui::ViewProviderPartReference);

public:
    /// constructor
    ViewProviderPartReference();
    /// destructor
    virtual ~ViewProviderPartReference();

    // Display properties
    //App::PropertyFloatConstraint LineWidth;
    //App::PropertyFloatConstraint PointSize;
    //App::PropertyColor LineColor;
    //App::PropertyColor PointColor;
    //App::PropertyMaterial LineMaterial;
    //App::PropertyMaterial PointMaterial;
    //App::PropertyBool ControlPoints;
    //App::PropertyEnumeration Lighting;


    virtual void attach(App::DocumentObject *);
    virtual void setDisplayMode(const char* ModeName);
    /// returns a list of all possible modes
    virtual std::vector<std::string> getDisplayModes(void) const;
    /// Update the view representation
    void reload();

    virtual void updateData(const App::Property*);

protected:
    /// get called by the container whenever a property has been changed
    virtual void onChanged(const App::Property* prop);
    //bool loadParameter();

    // nodes for the data representation
    SoGroup  *EdgeRoot;
    SoGroup  *FaceRoot;
    SoGroup  *VertexRoot;
    SoMaterial   *pcLineMaterial;
    SoMaterial   *pcPointMaterial;
    SoDrawStyle  *pcLineStyle;
    SoDrawStyle  *pcPointStyle;
    SoSwitch     *pcControlPoints;
    SoShapeHints *pShapeHints;

private:
    // settings stuff
    float meshDeviation;
    bool noPerVertexNormals;
    bool qualityNormals;
    static App::PropertyFloatConstraint::Constraints floatRange;
    static const char* LightingEnums[];
};



} // namespace PartGui


#endif // PARTGUI_ViewProviderPartReference_H

