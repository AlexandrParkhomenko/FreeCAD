/***************************************************************************
 *   Copyright (c) 2017 Markus Hovorka <m.hovorka@live.de>                 *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include <string>
#include <fstream>
#include <boost/signals2.hpp>

#include "DocumentObject.h"
#include "TextDocument.h"


using namespace App;

PROPERTY_SOURCE(App::TextDocument, App::DocumentObject)

TextDocument::TextDocument()
{
    ADD_PROPERTY_TYPE(
            Text, (""), 0, App::Prop_Hidden,
            "Content of the document.");
    ADD_PROPERTY_TYPE(
            ReadOnly, (false), 0, App::Prop_None,
            "Defines whether the content can be edited.");
}

void TextDocument::onChanged(const Property* prop)
{
    if (prop == &Text)
        textChanged();
    DocumentObject::onChanged(prop);
}

const char* TextDocument::getViewProviderName() const
{
    return "Gui::ViewProviderTextDocument";
}

boost::signals2::connection TextDocument::connect(const TextSlot &sub)
{
    return textChanged.connect(sub);
}
