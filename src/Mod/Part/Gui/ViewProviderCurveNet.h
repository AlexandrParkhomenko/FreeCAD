/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERCURVENET_H
#define PARTGUI_VIEWPROVIDERCURVENET_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace Gui {
  class View3DInventorViewer;
  class SoFCSelection;
}

namespace PartGui {


class PartGuiExport ViewProviderCurveNet:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderPart);

public:
    /// constructor
    ViewProviderCurveNet();
    /// destructor
    virtual ~ViewProviderCurveNet();

    virtual void attach(App::DocumentObject *);
    virtual void setDisplayMode(const char* ModeName);
    /// returns a list of all possible modes
    virtual std::vector<std::string> getDisplayModes(void) const;

    /// Update the Part representation
    virtual void updateData(const App::Property*);

    virtual bool handleEvent(const SoEvent * const ev,Gui::View3DInventorViewer &Viewer);

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);

    struct Node {
        Gui::SoFCSelection  *pcHighlight;
        SoTransform    *pcTransform;
        Node() {
            pcHighlight = 0;
            pcTransform = 0;
        }
    };

    std::list<Node> NodeList;

    bool bInEdit;
    bool bMovePointMode;
    Node PointToMove;
    /// root of the edge and vertex points
    SoSeparator *EdgeRoot, *VertexRoot;

    Standard_Boolean computeEdges   (SoSeparator* root, const TopoDS_Shape &myShape);
    Standard_Boolean computeVertices(SoSeparator* root, const TopoDS_Shape &myShape);
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERCURVENET_H

