/***************************************************************************
 *   Copyright (c) 2010 Juergen Riegel <FreeCAD@juergen-riegel.net>        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Mod/Part/App/BodyBasePy.h"
#include "App/Application.h"
#include "App/Document.h"
#include "Base/Placement.h"

#include "BodyBase.h"


namespace Part {


PROPERTY_SOURCE_WITH_EXTENSIONS(Part::BodyBase, Part::Feature)

BodyBase::BodyBase()
{
    ADD_PROPERTY(Tip         , (0) );
    Tip.setScope(App::LinkScope::Child);

    ADD_PROPERTY(BaseFeature , (0) );

    App::OriginGroupExtension::initExtension(this);
}

BodyBase* BodyBase::findBodyOf(const App::DocumentObject* f)
{
    App::Document* doc = f->getDocument();
    if (doc != NULL) {
        std::vector<App::DocumentObject*> bodies = doc->getObjectsOfType(BodyBase::getClassTypeId());
        for (std::vector<App::DocumentObject*>::const_iterator b = bodies.begin(); b != bodies.end(); b++) {
            BodyBase* body = static_cast<BodyBase*>(*b);
            if (body->hasObject(f))
                return body;
        }
    }

    return NULL;
}

bool BodyBase::isAfter(const App::DocumentObject *feature, const App::DocumentObject* target) const {
    assert (feature);

    if (feature == target) {
        return false;
    }

    if (!target || target == BaseFeature.getValue() ) {
        return hasObject (feature);
    }

    const std::vector<App::DocumentObject *> & features = Group.getValues();
    auto featureIt = std::find(features.begin(), features.end(), feature);
    auto targetIt = std::find(features.begin(), features.end(), target);

    if (featureIt == features.end()) {
        return false;
    } else {
        return featureIt > targetIt;
    }
}

void BodyBase::onBeforeChange (const App::Property* prop) {
    
    //Tip can't point outside the body, hence no base feature tip
    /*// If we are changing the base feature and tip point to it reset it
    if ( prop == &BaseFeature && BaseFeature.getValue() == Tip.getValue() && BaseFeature.getValue() ) {
        Tip.setValue( nullptr );
    }*/
    Part::Feature::onBeforeChange ( prop );
}

void BodyBase::onChanged (const App::Property* prop) {
    //Tip can't point outside the body, hence no base feature tip
    /*// If the tip is zero and we are adding a base feature to the body set it to be the tip
    if ( prop == &BaseFeature && !Tip.getValue() && BaseFeature.getValue() ) {
        Tip.setValue( BaseFeature.getValue () );
    }*/
    Part::Feature::onChanged ( prop );
}

void BodyBase::handleChangedPropertyName(Base::XMLReader &reader,
                                         const char * TypeName,
                                         const char *PropName)
{
    // The App::PropertyLinkList property was Model in the past (#0002642)
    Base::Type type = Base::Type::fromName(TypeName);
    if (Group.getClassTypeId() == type && strcmp(PropName, "Model") == 0) {
        Group.Restore(reader);
    }
    else {
        Part::Feature::handleChangedPropertyName(reader, TypeName, PropName);
    }
}

PyObject* BodyBase::getPyObject()
{
    if (PythonObject.is(Py::_None())){
        // ref counter is set to 1
        PythonObject = Py::Object(new BodyBasePy(this),true);
    }
    return Py::new_reference_to(PythonObject);
}

} /* Part */
