/***************************************************************************
 *   Copyright (c) 2017 Markus Hovorka <m.hovorka@live.de>                 *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_TEXTDOCUMENT_H
#define APP_TEXTDOCUMENT_H


#include "stdexport.h"
#include <string>
#include <boost/signals2.hpp>

#include "DocumentObject.h"
#include "PropertyStandard.h"


namespace App
{

class AppExport TextDocument : public App::DocumentObject {
    PROPERTY_HEADER(App::TextDocument);
public:
    using TextSignal = boost::signals2::signal<void ()>;
    using TextSlot = TextSignal::slot_type;

    PropertyString Text;
    PropertyBool ReadOnly;

    TextDocument();
    ~TextDocument() {};

    void onChanged(const Property* prop);
    const char* getViewProviderName() const;

    boost::signals2::connection connect(const TextSlot &sub);
private:
    TextSignal textChanged;
};

}


#endif
