/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_IEWPROVIDER2DOBJECT_H
#define PARTGUI_IEWPROVIDER2DOBJECT_H

#include "stdexport.h"
#include "ViewProvider.h"
#include "App/PropertyUnits.h"
#include "Gui/ViewProviderPythonFeature.h"

class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProvider2DObject: public PartGui::ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProvider2DObject);

public:
    /// constructor
    ViewProvider2DObject();
    /// destructor
    virtual ~ViewProvider2DObject();

    /// Property to switch the grid on and off
    App::PropertyBool ShowGrid;
    App::PropertyLength GridSize;
    App::PropertyEnumeration GridStyle;
    App::PropertyBool TightGrid;
    App::PropertyBool GridSnap;

    virtual void attach(App::DocumentObject *);
    virtual void updateData(const App::Property*);
    virtual std::vector<std::string> getDisplayModes(void) const;
    virtual const char* getDefaultDisplayMode() const;

    /// creates the grid
    SoSeparator* createGrid(void); 

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);
    /// get called by the container whenever a property has been changed
    virtual void onChanged(const App::Property* prop);
    virtual void Restore(Base::XMLReader &reader);
    virtual void handleChangedPropertyType(Base::XMLReader &reader, const char * TypeName, App::Property * prop);

    SoSeparator  *GridRoot;

    float MinX;
    float MaxX;
    float MinY;
    float MaxY;
    static const char* GridStyleEnums[];
    static App::PropertyQuantityConstraint::Constraints GridSizeRange;
};

typedef Gui::ViewProviderPythonFeatureT<ViewProvider2DObject> ViewProvider2DObjectPython;

} // namespace PartGui


#endif // PARTGUI_IEWPROVIDER2DOBJECT_H

