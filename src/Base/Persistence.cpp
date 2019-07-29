/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "Writer.h"
#include "Reader.h"
#include "PyObjectBase.h"

#include "Persistence.h"

using namespace Base;

TYPESYSTEM_SOURCE_ABSTRACT(Base::Persistence,Base::BaseClass);


//**************************************************************************
// Construction/Destruction



//**************************************************************************
// separator for other implementation aspects

unsigned int Persistence::getMemSize (void) const
{
    // you have to implement this method in all descending classes!
    assert(0);
    return 0;
}

void Persistence::Save (Writer &/*writer*/) const
{
    // you have to implement this method in all descending classes!
    assert(0);
}

void Persistence::Restore(XMLReader &/*reader*/)
{
    // you have to implement this method in all descending classes!
    assert(0);
}

void Persistence::SaveDocFile (Writer &/*writer*/) const
{
}

void Persistence::RestoreDocFile(Reader &/*reader*/)
{
}

std::string Persistence::encodeAttribute(const std::string& str)
{
    std::string tmp;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (*it == '<')
            tmp += "&lt;";
        else if (*it == '\"')
            tmp += "&quot;";
        else if (*it == '\'')
            tmp += "&apos;";
        else if (*it == '&')
            tmp += "&amp;";
        else if (*it == '>')
            tmp += "&gt;";
        else if (*it == '\r')
            tmp += "&#13;";
        else if (*it == '\n')
            tmp += "&#10;";
        else if (*it == '\t')
            tmp += "&#9;";
        else
            tmp += *it;
    }

    return tmp;
}

