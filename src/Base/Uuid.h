/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef BASE_UUID_H
#define BASE_UUID_H

#include "stdexport.h"
#include <string>

namespace Base
{

/** Creates a Uuid
 * \author Jürgen Riegel
 */
class BaseExport Uuid
{
public:
    /// Construction
    Uuid();
    /// Destruction
    virtual ~Uuid();

    void setValue(const char* sString);
    void setValue(const std::string &sString);
    const std::string& getValue(void) const;
    static std::string createUuid(void);

private:
    std::string _uuid;
};

} //namespace Base

#endif // BASE_UUID_H

