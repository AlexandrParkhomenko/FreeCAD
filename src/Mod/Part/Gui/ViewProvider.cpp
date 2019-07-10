/***************************************************************************
 *   Copyright (c) 2004 Juergen Riegel <juergen.riegel@web.de>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "Base/Console.h"
#include "Base/Exception.h"
#include "Gui/Command.h"

#include "Mod/Part/App/PartFeature.h"

#include "ViewProvider.h"


using namespace PartGui;

PROPERTY_SOURCE(PartGui::ViewProviderPart, PartGui::ViewProviderPartExt)


ViewProviderPart::ViewProviderPart()
{
}

ViewProviderPart::~ViewProviderPart()
{
}

bool ViewProviderPart::doubleClicked(void)
{
    std::string Msg("Edit ");
    Msg += this->pcObject->Label.getValue();
    try {
        Gui::Command::openCommand(Msg.c_str());
        Gui::Command::doCommand(Gui::Command::Gui,"Gui.ActiveDocument.setEdit('%s',0)",
                                this->pcObject->getNameInDocument());
        return true;
    }
    catch (const Base::Exception& e) {
        Base::Console().Error("%s\n", e.what());
        return false;
    }
}

void ViewProviderPart::applyColor(const Part::ShapeHistory& hist,
                                  const std::vector<App::Color>& colBase,
                                  std::vector<App::Color>& colBool)
{
    std::map<int, std::vector<int> >::const_iterator jt;
    // apply color from modified faces
    for (jt = hist.shapeMap.begin(); jt != hist.shapeMap.end(); ++jt) {
        std::vector<int>::const_iterator kt;
        for (kt = jt->second.begin(); kt != jt->second.end(); ++kt) {
            colBool[*kt] = colBase[jt->first];
        }
    }
}

void ViewProviderPart::applyTransparency(const float& transparency,
                                  std::vector<App::Color>& colors)
{
    if (transparency != 0.0) {
        // transparency has been set object-wide
        std::vector<App::Color>::iterator j;
        for (j = colors.begin(); j != colors.end(); ++j) {
            // transparency hasn't been set for this face
            if (j->a == 0.0)
                j->a = transparency/100.0; // transparency comes in percent
        }
    }
}

// ----------------------------------------------------------------------------

void ViewProviderShapeBuilder::buildNodes(const App::Property* , std::vector<SoNode*>& ) const
{
}

void ViewProviderShapeBuilder::createShape(const App::Property* , SoSeparator* ) const
{
}
