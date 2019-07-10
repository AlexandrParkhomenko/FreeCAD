/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDERANNOTATION_H
#define GUI_VIEWPROVIDERANNOTATION_H

#include "stdexport.h"
#include "ViewProviderDocumentObject.h"
#include "App/PropertyUnits.h"

class SoFont;
class SoText2;
class SoAsciiText;
class SoBaseColor;
class SoTranslation;
class SoTransform;
class SoRotationXYZ;
class SoImage;
class SoCoordinate3;

namespace Gui
{

class GuiExport ViewProviderAnnotation : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderAnnotation);

public:
    /// Constructor
    ViewProviderAnnotation(void);
    virtual ~ViewProviderAnnotation();

    // Display properties
    App::PropertyColor          TextColor;
    App::PropertyEnumeration    Justification;
    App::PropertyFloat          FontSize;
    App::PropertyFont           FontName;
    App::PropertyFloat          LineSpacing;
    App::PropertyAngle          Rotation;
    App::PropertyEnumeration    RotationAxis;

    void attach(App::DocumentObject *);
    void updateData(const App::Property*);
    std::vector<std::string> getDisplayModes(void) const;
    void setDisplayMode(const char* ModeName);

protected:
    void onChanged(const App::Property* prop);

private:
    SoFont           * pFont;
    SoText2          * pLabel;
    SoAsciiText      * pLabel3d;
    SoBaseColor      * pColor;
    SoTranslation    * pTranslation;
    SoRotationXYZ    * pRotationXYZ;

    static const char* JustificationEnums[];
    static const char* RotationAxisEnums[];
};

/**
 * This is a different implementation of an annotation object which uses an
 * SoImage node instead of an SoText2 or SoAsciiText node.
 * This approach gives a bit more flexibility since it can render arbitrary
 * annotations.
 */
class GuiExport ViewProviderAnnotationLabel : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderAnnotationLabel);

public:
    /// Constructor
    ViewProviderAnnotationLabel(void);
    virtual ~ViewProviderAnnotationLabel();

    // Display properties
    App::PropertyColor          TextColor;
    App::PropertyColor          BackgroundColor;
    App::PropertyEnumeration    Justification;
    App::PropertyFloat          FontSize;
    App::PropertyFont           FontName;
    App::PropertyBool           Frame;

    void attach(App::DocumentObject *);
    void updateData(const App::Property*);
    std::vector<std::string> getDisplayModes(void) const;
    void setDisplayMode(const char* ModeName);

    /** @name Edit methods */
    //@{
    bool doubleClicked(void);
    void setupContextMenu(QMenu*, QObject*, const char*);
protected:
    bool setEdit(int ModNum);
    void unsetEdit(int ModNum);
    //@}

protected:
    void onChanged(const App::Property* prop);
    void drawImage(const std::vector<std::string>&);

private:
    static void dragStartCallback(void * data, SoDragger * d);
    static void dragFinishCallback(void * data, SoDragger * d);
    static void dragMotionCallback(void * data, SoDragger * d);

private:
    SoCoordinate3    * pCoords;
    SoImage          * pImage;
    SoBaseColor      * pColor;
    SoTranslation    * pBaseTranslation;
    SoTransform      * pTextTranslation;

    static const char* JustificationEnums[];
};

} //namespace Gui


#endif // GUI_VIEWPROVIDERANNOTATION_H
