/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2012    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_ViewProviderPlacement_H
#define GUI_ViewProviderPlacement_H

#include "stdexport.h"
#include "ViewProviderGeometryObject.h"
#include <QObject>

class SoFontStyle;
class SoText2;
class SoBaseColor;
class SoTranslation;
class SoCoordinate3;
class SoIndexedLineSet;
class SoEventCallback;
class SoMaterial;

namespace Gui
{


class GuiExport ViewProviderPlacement : public ViewProviderGeometryObject
{
    PROPERTY_HEADER(Gui::ViewProviderPlacement);

public:
    /// Constructor
    ViewProviderPlacement(void);
    virtual ~ViewProviderPlacement();

    void attach(App::DocumentObject *);
    void updateData(const App::Property*);
    std::vector<std::string> getDisplayModes(void) const;
    void setDisplayMode(const char* ModeName);

    /// indicates if the ViewProvider use the new Selection model
    virtual bool useNewSelectionModel(void) const {return true;}
    /// indicates if the ViewProvider can be selected
    virtual bool isSelectable(void) const ;
    /// return a hit element to the selection path or 0
    virtual std::string getElement(const SoDetail *) const;
    virtual SoDetail* getDetail(const char*) const;

protected:
    void onChanged(const App::Property* prop);

private:
    SoCoordinate3    * pCoords;
    SoMaterial       * pMat;
    SoIndexedLineSet * pLines;
};

} //namespace Gui


#endif // GUI_ViewProviderPlacement_H
