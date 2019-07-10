/***************************************************************************
 *   Copyright (c) 2009 Juergen Riegel (FreeCAD@juergen-riegel.net)             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include <sstream>

#include "App/Application.h"
#include "App/Document.h"
#include "App/DocumentObject.h"
#include "Base/Interpreter.h"

#include "SelectionObject.h"
#include "Selection.h"
#include "Application.h"
#include "Gui/SelectionObjectPy.h"

using namespace Gui;


TYPESYSTEM_SOURCE_ABSTRACT(Gui::SelectionObject, Base::BaseClass)

SelectionObject::SelectionObject()
{
}

SelectionObject::SelectionObject(const Gui::SelectionChanges& msg)
{
    FeatName = msg.pObjectName ? msg.pObjectName : "";
    DocName = msg.pDocName ? msg.pDocName : "";
    TypeName = msg.pTypeName ? msg.pTypeName : "";
    if (msg.pSubName) {
        SubNames.push_back(msg.pSubName);
        SelPoses.push_back(Base::Vector3d(msg.x, msg.y, msg.z));
    }
}

SelectionObject::SelectionObject(App::DocumentObject* obj)
{
    FeatName = obj->getNameInDocument();
    DocName = obj->getDocument()->getName();
    TypeName = obj->getTypeId().getName();
}

SelectionObject::~SelectionObject()
{
}

const App::DocumentObject * SelectionObject::getObject(void) const
{
    if (!DocName.empty()) {
        App::Document *doc = App::GetApplication().getDocument(DocName.c_str());
        if (doc && !FeatName.empty())
            return doc->getObject(FeatName.c_str());
    }
    return 0;
}

App::DocumentObject * SelectionObject::getObject(void) 
{
    if (!DocName.empty()) {
        App::Document *doc = App::GetApplication().getDocument(DocName.c_str());
        if (doc && !FeatName.empty())
            return doc->getObject(FeatName.c_str());
    }
    return 0;
}

bool SelectionObject::isObjectTypeOf(const Base::Type& typeId) const
{
    const App::DocumentObject* obj = getObject();
    return (obj && obj->getTypeId().isDerivedFrom(typeId));
}

std::string SelectionObject::getAsPropertyLinkSubString(void)const
{
    std::string buf;
    buf += "(App.";
    buf += "ActiveDocument";//getObject()->getDocument()->getName(); 
    buf += ".";
    buf += getObject()->getNameInDocument(); 
    buf += ",[";
    for(std::vector<std::string>::const_iterator it = SubNames.begin();it!=SubNames.end();++it){
        buf += "\""; 
        buf += *it; 
        buf += "\"";
        if(it != --SubNames.end())
            buf += ",";
    }
    buf += "])";
   
    return buf;
}

PyObject* SelectionObject::getPyObject()
{
    return new SelectionObjectPy(new SelectionObject(*this));
}
