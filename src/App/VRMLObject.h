/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_VRMLOROBJECT_H
#define APP_VRMLOROBJECT_H

#include "stdexport.h"
#include "GeoFeature.h"
#include "PropertyFile.h"


namespace App
{

class AppExport VRMLObject : public GeoFeature
{
    PROPERTY_HEADER(App::VRMLObject);

public:
    /// Constructor
    VRMLObject(void);
    virtual ~VRMLObject();

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "Gui::ViewProviderVRMLObject";
    }
    virtual DocumentObjectExecReturn *execute(void) {
        return DocumentObject::StdReturn;
    }
    virtual short mustExecute(void) const;
    virtual PyObject *getPyObject(void);
    virtual void Save (Base::Writer &writer) const;
    virtual void Restore(Base::XMLReader &reader);
    virtual void SaveDocFile (Base::Writer &writer) const;
    virtual void RestoreDocFile(Base::Reader &reader);

    PropertyFileIncluded VrmlFile;
    PropertyStringList Urls;
    PropertyStringList Resources;

protected:
    void onChanged(const App::Property*);
    std::string getRelativePath(const std::string&, const std::string&) const;
    std::string fixRelativePath(const std::string&, const std::string&) const;
    void makeDirectories(const std::string&, const std::string&);

private:
    mutable std::string vrmlPath;
    mutable int index;
};

} //namespace App


#endif // APP_INVENTOROBJECT_H
