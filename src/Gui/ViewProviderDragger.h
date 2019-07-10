/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_DRAGGER_H
#define GUI_VIEWPROVIDER_DRAGGER_H

#include "stdexport.h"
#include "ViewProviderDocumentObject.h"

class SoDragger;
class SoTransform;

namespace Base { class Placement;}

namespace Gui {

class View3DInventorViewer;
class SoFCCSysDragger;

/**
 * The base class for all view providers modifying the placement
 * of a geometric feature.
 * @author Werner Mayer
 */
class GuiExport ViewProviderDragger : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderDragger);

public:
    /// constructor.
    ViewProviderDragger();

    /// destructor.
    virtual ~ViewProviderDragger();

    /** @name Edit methods */
    //@{
    bool doubleClicked(void);
    void setupContextMenu(QMenu*, QObject*, const char*);
    void updateData(const App::Property*);

    /*! synchronize From FC placement to Coin placement*/
    static void updateTransform(const Base::Placement &from, SoTransform *to);

protected:
    bool setEdit(int ModNum);
    void unsetEdit(int ModNum);
    void setEditViewer(View3DInventorViewer*, int ModNum);
    void unsetEditViewer(View3DInventorViewer*);
    //@}
    SoFCCSysDragger *csysDragger = nullptr;

private:
    static void dragStartCallback(void * data, SoDragger * d);
    static void dragFinishCallback(void * data, SoDragger * d);
    
    static void updatePlacementFromDragger(ViewProviderDragger *sudoThis, SoFCCSysDragger *draggerIn);
};

} // namespace Gui


#endif // GUI_VIEWPROVIDER_DRAGGER_H

