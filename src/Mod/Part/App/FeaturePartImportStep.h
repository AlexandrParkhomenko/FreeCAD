/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef PART_FEATUREPARTIMPORTSTEP_H
#define PART_FEATUREPARTIMPORTSTEP_H


#include "App/PropertyStandard.h"

#include "PartFeature.h"



namespace Part
{


class ImportStep :public Part::Feature
{
    PROPERTY_HEADER(Part::FeaturePartImportStep);

public:
    ImportStep();

    App::PropertyString FileName;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderImport";
    }
    //@}
};

}


#endif // PART_FEATUREPARTIMPORTSTEP_H
