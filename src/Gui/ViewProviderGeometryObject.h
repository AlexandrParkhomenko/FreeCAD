/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_GEOMETRYOBJECT_H
#define GUI_VIEWPROVIDER_GEOMETRYOBJECT_H

#include "stdexport.h"
#include "ViewProviderDragger.h"
#include <Inventor/lists/SoPickedPointList.h>

class SoPickedPointList;
class SoSwitch;
class SoSensor;
class SbVec2s;
class SoBaseColor;

namespace Gui {

class SoFCSelection;
class SoFCBoundingBox;
class View3DInventorViewer;

/**
 * The base class for all view providers that display geometric data, like mesh, point cloudes and shapes.
 * @author Werner Mayer
 */
class GuiExport ViewProviderGeometryObject : public ViewProviderDragger
{
    PROPERTY_HEADER(Gui::ViewProviderGeometryObject);

public:
    /// constructor.
    ViewProviderGeometryObject();

    /// destructor.
    virtual ~ViewProviderGeometryObject();

    // Display properties
    App::PropertyColor ShapeColor;
    App::PropertyPercent Transparency;
    App::PropertyMaterial ShapeMaterial;
    App::PropertyBool BoundingBox;
    App::PropertyBool Selectable;
    App::PropertyEnumeration SelectionStyle;

    /**
     * Attaches the document object to this view provider.
     */
    void attach(App::DocumentObject *pcObject);
    void updateData(const App::Property*);

    bool isSelectable(void) const {return Selectable.getValue();}

    /**
     * Returns a list of picked points from the geometry under \a getRoot().
     * If \a pickAll is false (the default) only the intersection point closest to the camera will be picked, otherwise
     * all intersection points will be picked. 
     */
    SoPickedPointList getPickedPoints(const SbVec2s& pos, const View3DInventorViewer& viewer,bool pickAll=false) const;
    /**
     * This method is provided for convenience and does basically the same as getPickedPoints() unless that only the closest
     * point to the camera will be picked.
     * \note It is in the response of the client programmer to delete the returned SoPickedPoint object.
     */
    SoPickedPoint* getPickedPoint(const SbVec2s& pos, const View3DInventorViewer& viewer) const;

    /** @name Edit methods */
    //@{
    virtual void showBoundingBox(bool);
    //@}

protected:
    /// get called by the container whenever a property has been changed
    void onChanged(const App::Property* prop);
    void setSelectable(bool Selectable=true);

    virtual unsigned long getBoundColor() const;

protected:
    SoMaterial       * pcShapeMaterial;
    SoFCBoundingBox  * pcBoundingBox;
    SoSwitch         * pcBoundSwitch;
    SoBaseColor      * pcBoundColor;
};

} // namespace Gui


#endif // GUI_VIEWPROVIDER_GEOMETRYOBJECT_H

