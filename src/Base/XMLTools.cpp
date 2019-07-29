/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <assert.h>

#include "XMLTools.h"

using namespace Base;

std::unique_ptr<XERCES_CPP_NAMESPACE::XMLTranscoder> StrXUTF8::transcoder;
std::unique_ptr<XERCES_CPP_NAMESPACE::XMLTranscoder> XUTF8Str::transcoder;

void StrXUTF8::terminate()
{
    transcoder.reset();
}

void XUTF8Str::terminate()
{
    transcoder.reset();
}
