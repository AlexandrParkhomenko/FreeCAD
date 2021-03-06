/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QUuid>

#include <stdexcept>

#include "Uuid.h"
#include "Exception.h"
#include "Interpreter.h"
#include <stdexcept>
#include <CXX/Objects.hxx>


using namespace Base;


//**************************************************************************
// Construction/Destruction

/**
 * A constructor.
 * A more elaborate description of the constructor.
 */
Uuid::Uuid()
{
    _uuid = createUuid();
}

/**
 * A destructor.
 * A more elaborate description of the destructor.
 */
Uuid::~Uuid()
{
}

//**************************************************************************
//**************************************************************************
// Get the UUID
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string Uuid::createUuid(void)
{
    std::string Uuid;
    QString uuid = QUuid::createUuid().toString();
    uuid = uuid.mid(1);
    uuid.chop(1);
    Uuid = (const char*)uuid.toUtf8();
    return Uuid;
}

void Uuid::setValue(const char* sString) 
{ 
    if (sString) { 
        QUuid quuid(sString); 
        if (quuid.isNull()) 
            throw std::runtime_error("invalid uuid"); 
        // remove curly braces 
        QString id = quuid.toString(); 
        id = id.mid(1); 
        id.chop(1); 
        _uuid = (const char*)id.toUtf8(); 
    } 
} 

void Uuid::setValue(const std::string &sString)
{
    setValue(sString.c_str());
}

const std::string& Uuid::getValue(void) const
{
    return _uuid;
}
