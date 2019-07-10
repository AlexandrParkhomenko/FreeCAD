/***************************************************************************
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef VIEWPROVIDEORIGINFEATURE_H_BYJRZNDL
#define VIEWPROVIDEORIGINFEATURE_H_BYJRZNDL

#include "stdexport.h"
#include "ViewProviderGeometryObject.h"

class SoAsciiText;
class SoScale;

namespace Gui
{

/**
 * View provider associated with an App::OriginFeature.
 */
class GuiExport ViewProviderOriginFeature: public ViewProviderGeometryObject {
    PROPERTY_HEADER(Gui::ViewProviderOriginFeature);

public:
    /// The display size of the feature
    App::PropertyFloat  Size;

    ViewProviderOriginFeature ();
    virtual ~ViewProviderOriginFeature ();

    /// Get point derived classes will add their specific stuff
    SoSeparator * getOriginFeatureRoot () { return pOriginFeatureRoot; }

    /// Get pointer to the text label associated with the feature
    SoAsciiText * getLabel () { return pLabel; }

    virtual void attach(App::DocumentObject *);
    virtual void updateData(const App::Property *);
    virtual std::vector<std::string> getDisplayModes () const;
    virtual void setDisplayMode (const char* ModeName);

    /// @name Suppress ViewProviderGeometryObject's behaviour
    ///@{
    virtual bool setEdit ( int )
        { return false; }
    virtual void unsetEdit ( int )
        { }
    ///@}

protected:
    virtual void onChanged ( const App::Property* prop );
    virtual bool onDelete ( const std::vector<std::string> & );
protected:
    SoSeparator    * pOriginFeatureRoot;
    SoScale        * pScale;
    SoAsciiText    * pLabel;
};

} /* Gui */

#endif /* end of include guard: VIEWPROVIDEORIGINFEATURE_H_BYJRZNDL */
