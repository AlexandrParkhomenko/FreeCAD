/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DlgEditFileIncludePropertyExternal_H
#define GUI_DIALOG_DlgEditFileIncludePropertyExternal_H

#include "stdexport.h"
#include "DlgRunExternal.h"
#include "App/PropertyFile.h"

namespace Gui {
namespace Dialog {

/**
 * 
 * \author Jürgen Riegel
 */
class GuiExport DlgEditFileIncludePropertyExternal : public DlgRunExternal 
{ 
    Q_OBJECT

public:
    DlgEditFileIncludePropertyExternal( App::PropertyFileIncluded& Prop, QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    virtual ~DlgEditFileIncludePropertyExternal();

    int Do(void);

protected Q_SLOTS:
protected:
    App::PropertyFileIncluded& Prop;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DlgEditFileIncludePropertyExternal_H
