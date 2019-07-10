/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef POINTSGUI_VIEWPROVIDERPOINTS_H
#define POINTSGUI_VIEWPROVIDERPOINTS_H

#include "stdexport.h"
#include "Base/Vector3D.h"
#include "Gui/ViewProviderGeometryObject.h"
#include "Gui/ViewProviderPythonFeature.h"
#include "Gui/ViewProviderBuilder.h"
#include <Inventor/SbVec2f.h>


class SoSwitch;
class SoPointSet;
class SoIndexedPointSet;
class SoLocateHighlight;
class SoCoordinate3;
class SoNormal;
class SoEventCallback;

namespace App {
    class PropertyColorList;
}

namespace Gui {
    class SoFCSelection;
}

namespace Points {
    class PropertyGreyValueList;
    class PropertyNormalList;
    class PointKernel;
    class Feature;
}

namespace PointsGui {

class ViewProviderPointsBuilder : public Gui::ViewProviderBuilder
{
public:
    ViewProviderPointsBuilder(){}
    ~ViewProviderPointsBuilder(){}
    virtual void buildNodes(const App::Property*, std::vector<SoNode*>&) const;
    void createPoints(const App::Property*, SoCoordinate3*, SoPointSet*) const;
    void createPoints(const App::Property*, SoCoordinate3*, SoIndexedPointSet*) const;
};

/**
 * The ViewProviderPoints class creates
 * a node representing the point data structure.
 * @author Werner Mayer
 */
class PointsGuiExport ViewProviderPoints : public Gui::ViewProviderGeometryObject
{
    PROPERTY_HEADER(PointsGui::ViewProviderPoints);

public:
    ViewProviderPoints();
    virtual ~ViewProviderPoints();

    App::PropertyFloatConstraint PointSize;

    /// set the viewing mode
    virtual void setDisplayMode(const char* ModeName);
    /// returns a list of all possible modes
    virtual std::vector<std::string> getDisplayModes(void) const;
    virtual QIcon getIcon() const;

    /// Sets the edit mnode
    bool setEdit(int ModNum);
    /// Unsets the edit mode
    void unsetEdit(int ModNum);

public:
    static void clipPointsCallback(void * ud, SoEventCallback * n);

protected:
    void onChanged(const App::Property* prop);
    void setVertexColorMode(App::PropertyColorList*);
    void setVertexGreyvalueMode(Points::PropertyGreyValueList*);
    void setVertexNormalMode(Points::PropertyNormalList*);
    virtual void cut(const std::vector<SbVec2f>& picked, Gui::View3DInventorViewer &Viewer) = 0;

protected:
    Gui::SoFCSelection  * pcHighlight;
    SoCoordinate3       * pcPointsCoord;
    SoMaterial          * pcColorMat;
    SoNormal            * pcPointsNormal;
    SoDrawStyle         * pcPointStyle;

private:
    static App::PropertyFloatConstraint::Constraints floatRange;
};

/**
 * The ViewProviderScattered class creates
 * a node representing the scattered point cloud.
 * @author Werner Mayer
 */
class PointsGuiExport ViewProviderScattered : public ViewProviderPoints
{
    PROPERTY_HEADER(PointsGui::ViewProviderScattered);

public:
    ViewProviderScattered();
    virtual ~ViewProviderScattered();

    /**
     * Extracts the point data from the feature \a pcFeature and creates
     * an Inventor node \a SoNode with these data. 
     */
    virtual void attach(App::DocumentObject *);
    /// Update the point representation
    virtual void updateData(const App::Property*);

protected:
    virtual void cut(const std::vector<SbVec2f>& picked, Gui::View3DInventorViewer &Viewer);

protected:
    SoPointSet          * pcPoints;
};

/**
 * The ViewProviderStructured class creates
 * a node representing the structured points.
 * @author Werner Mayer
 */
class PointsGuiExport ViewProviderStructured : public ViewProviderPoints
{
    PROPERTY_HEADER(PointsGui::ViewProviderStructured);

public:
    ViewProviderStructured();
    virtual ~ViewProviderStructured();

    /**
     * Extracts the point data from the feature \a pcFeature and creates
     * an Inventor node \a SoNode with these data. 
     */
    virtual void attach(App::DocumentObject *);
    /// Update the point representation
    virtual void updateData(const App::Property*);

protected:
    virtual void cut(const std::vector<SbVec2f>& picked, Gui::View3DInventorViewer &Viewer);

protected:
    SoIndexedPointSet   * pcPoints;
};

typedef Gui::ViewProviderPythonFeatureT<ViewProviderScattered> ViewProviderPython;

} // namespace PointsGui


#endif // POINTSGUI_VIEWPROVIDERPOINTS_H

