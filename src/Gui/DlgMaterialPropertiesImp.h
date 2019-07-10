/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGMATERIALPROPERTIES_IMP_H
#define GUI_DIALOG_DLGMATERIALPROPERTIES_IMP_H

#include "ui_DlgMaterialProperties.h"
#include <vector>

namespace Gui {
class ViewProvider;

namespace Dialog {

class DlgMaterialPropertiesImp : public QDialog, public Ui_DlgMaterialProperties
{
    Q_OBJECT

public:
    DlgMaterialPropertiesImp(const std::string& mat, QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgMaterialPropertiesImp();
    void setViewProviders(const std::vector<Gui::ViewProvider*>&);

public Q_SLOTS:
    void on_ambientColor_changed();
    void on_diffuseColor_changed();
    void on_emissiveColor_changed();
    void on_specularColor_changed();
    void on_shininess_valueChanged(int);

private:
    std::string material;
    std::vector<Gui::ViewProvider*> Objects;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGMATERIALPROPERTIES_IMP_H

