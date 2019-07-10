/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef __FeatureImportStep_H__
#define __FeatureImportStep_H__


#include "Mod/Part/App/PartFeature.h"

namespace Import
{


  class FeatureImportStep :public Part::Feature
{
public:

	virtual void InitLabel(const TDF_Label &rcLabel);

	virtual Standard_Integer Execute(void);

//	virtual void Validate(void);

  /// Returns the Name/Type of the feature
  virtual const char *Type(void){return "PartImportStep";};
};



}




#endif // __FeatureImportStep_H__
