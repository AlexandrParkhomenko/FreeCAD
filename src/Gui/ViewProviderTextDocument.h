/***************************************************************************
 *   Copyright (c) 2017 Markus Hovorka <m.hovorka@live.de>                 *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_ViewProviderTextDocument_H
#define GUI_ViewProviderTextDocument_H


#include "stdexport.h"
#include "ViewProviderDocumentObject.h"


namespace Gui {

class GuiExport ViewProviderTextDocument : public ViewProviderDocumentObject {
    PROPERTY_HEADER(Gui::ViewProviderTextDocument);
public:
    ViewProviderTextDocument();
    ~ViewProviderTextDocument() {}

    bool doubleClicked();
    void setupContextMenu(QMenu* menu, QObject* receiver, const char* member);
    bool isShow() const { return true; }
private:
    bool activateView() const;
};

}

#endif

