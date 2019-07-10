/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QUuid>

#include <stdexcept>

/// Here the FreeCAD includes sorted by Base,App,Gui......
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
    Uuid = (const char*)uuid.toLatin1();
    return Uuid;
}

void Uuid::setValue(const char* sString) 
{ 
    if (sString) { 
        QUuid uuid(QString::fromLatin1(sString)); 
        if (uuid.isNull()) 
            throw std::runtime_error("invalid uuid"); 
        // remove curly braces 
        QString id = uuid.toString(); 
        id = id.mid(1); 
        id.chop(1); 
        _uuid = (const char*)id.toLatin1(); 
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
