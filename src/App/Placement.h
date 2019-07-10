/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#ifndef _AppPlacement_h_
#define _AppPlacement_h_

#include "stdexport.h"
#include "Base/Placement.h"

#include "GeoFeature.h"
#include "PropertyGeo.h"


namespace Base
{
//  class Vector3D;
  //class Matrix4D;
}

//using Base::Vector3D;
//using Base::Matrix4D;

namespace App
{


/** Placement Object
 *  Handles the repositioning of data. Also can do grouping
 */
class AppExport Placement: public App::GeoFeature
{
    PROPERTY_HEADER(App::Placement);

public:


  /// Constructor
  Placement(void);
  virtual ~Placement();
  
  /// returns the type name of the ViewProvider
  virtual const char* getViewProviderName(void) const {
      return "Gui::ViewProviderPlacement";
  }


};




} //namespace App



#endif
