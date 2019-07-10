/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2014     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 **************************************************************************


#ifndef APP_Path_H
#define APP_Path_H

#include "stdexport.h"
#include "Base/Persistence.h"



namespace App
{


// Base class of all geometric document objects.

class AppExport Path 
{
protected:
	std::vector<Base::Persistence *> _PathVector;

public:
    /// Constructor
    Path(void);
	Path(const std::vector<Base::Persistence *> & PathVector);

    virtual ~Path();

	const std::vector<Base::Persistence *> & getVector(void)const{return _PathVector;}

};

} //namespace App


#endif // APP_Path_H
*/
