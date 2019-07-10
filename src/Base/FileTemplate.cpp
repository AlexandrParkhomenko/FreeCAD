/***************************************************************************
 *   Copyright (c) YEAR YOUR NAME         <Your e-mail address>            *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




/// Here the FreeCAD includes sorted by Base,App,Gui......
#include "FileTemplate.h"


using namespace Base;


//**************************************************************************
// Construction/Destruction

/**
 * A constructor.
 * A more elaborate description of the constructor.
 */
ClassTemplate::ClassTemplate()
  : enumPtr(0)
  , enumVar(TVal1)
  , publicVar(0)
  , handler(0)
{
}

/**
 * A destructor.
 * A more elaborate description of the destructor.
 */
ClassTemplate::~ClassTemplate()
{
}


//**************************************************************************
// separator for other implementation aspects

/**
 * a normal member taking two arguments and returning an integer value.
 * \par
 * You can use a printf like interface like:
 * \code
 * GetConsole().Warning("Some defects in %s, loading anyway\n",str);
 * \endcode
 * @param a an integer argument.
 * @param s a constant character pointer.
 * @see ClassTemplate()
 * @see ~ClassTemplate()
 * @see testMeToo()
 * @see publicVar()
 * @return The test results
 */
int ClassTemplate::testMe(int /*a*/,const char* /*s*/)
{
    return 0;
}


//**************************************************************************
//**************************************************************************
// Separator for additional classes
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



