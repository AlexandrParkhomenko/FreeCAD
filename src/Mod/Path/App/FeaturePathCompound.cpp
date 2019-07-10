/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#include "stdexport.h"
#include "FeaturePathCompound.h"
#include "Command.h"
#include "Path.h"
#include "FeaturePathCompoundPy.h"
#include "App/FeaturePythonPyImp.h"

using namespace Path;
using namespace App;

PROPERTY_SOURCE(Path::FeatureCompound, Path::Feature)


FeatureCompound::FeatureCompound()
{
    ADD_PROPERTY_TYPE( Group,         (0),   "Base",Prop_None,"Ordered list of paths to combine");
    ADD_PROPERTY_TYPE( UsePlacements, (false), "Base",Prop_None,"Specifies if the placements of children must be computed");
}

FeatureCompound::~FeatureCompound()
{
}

App::DocumentObjectExecReturn *FeatureCompound::execute(void)
{
    const std::vector<DocumentObject*> &Paths = Group.getValues();
    Path::Toolpath result;

    for (std::vector<DocumentObject*>::const_iterator it= Paths.begin();it!=Paths.end();++it) {
        if ((*it)->getTypeId().isDerivedFrom(Path::Feature::getClassTypeId())){
            const std::vector<Command*> &cmds = static_cast<Path::Feature*>(*it)->Path.getValue().getCommands();
            const Base::Placement pl = static_cast<Path::Feature*>(*it)->Placement.getValue();
            for (std::vector<Command*>::const_iterator it2= cmds.begin();it2!=cmds.end();++it2) {
                if (UsePlacements.getValue() == true) {
                    result.addCommand((*it2)->transform(pl));
                } else {
                    result.addCommand(**it2);
                }
            }
        } else {
            return new App::DocumentObjectExecReturn("Not all objects in group are paths!");
        }
    }

    result.setCenter(Path.getValue().getCenter());
    Path.setValue(result);
    
    return App::DocumentObject::StdReturn;
}

bool FeatureCompound::hasObject(const DocumentObject* obj) const
{
    const std::vector<DocumentObject*>& grp = Group.getValues();
    for (std::vector<DocumentObject*>::const_iterator it = grp.begin(); it != grp.end(); ++it) {
        if (*it == obj)
            return true;
    }

    return false;
}

void FeatureCompound::addObject(DocumentObject* obj)
{
    if (!hasObject(obj)) {
        std::vector<DocumentObject*> grp = Group.getValues();
        grp.push_back(obj);
        Group.setValues(grp);
    }
}

void FeatureCompound::removeObject(DocumentObject* obj)
{
    std::vector<DocumentObject*> grp = Group.getValues();
    for (std::vector<DocumentObject*>::iterator it = grp.begin(); it != grp.end(); ++it) {
        if (*it == obj) {
            grp.erase(it);
            Group.setValues(grp);
            break;
        }
    }
}

PyObject *FeatureCompound::getPyObject()
{
    if (PythonObject.is(Py::_None())){
        // ref counter is set to 1
        PythonObject = Py::Object(new FeaturePathCompoundPy(this),true);
    }
    return Py::new_reference_to(PythonObject);
}

// Python Path Compound feature ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Path::FeatureCompoundPython, Path::FeatureCompound)
template<> const char* Path::FeatureCompoundPython::getViewProviderName(void) const {
    return "PathGui::ViewProviderPathCompoundPython";
}
/// @endcond

// explicit template instantiation
template class Standard_EXPORT FeaturePythonT<Path::FeatureCompound>;
}
