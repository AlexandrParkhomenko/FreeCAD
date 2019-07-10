/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGDISPLAYPROPERTIES_IMP_H
#define GUI_DIALOG_DLGDISPLAYPROPERTIES_IMP_H

#include <vector>
#include <boost/signals2.hpp>

#include "ui_DlgDisplayProperties.h"
#include "Selection.h"
#include "App/Material.h"

namespace App
{
  class Property;
}

namespace Gui {

  class ViewProvider;
  class Command;

namespace Dialog {
typedef boost::signals2::connection DlgDisplayPropertiesImp_Connection;

/**
 * The DlgDisplayPropertiesImp class implements a dialog containing all available document
 * templates to create a new document.
 * \author Jürgen Riegel
 */
class DlgDisplayPropertiesImp : public QDialog, public Ui_DlgDisplayProperties,
                                public Gui::SelectionSingleton::ObserverType
{
    Q_OBJECT

public:
    DlgDisplayPropertiesImp( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~DlgDisplayPropertiesImp();
    /// Observer message from the Selection
    void OnChange(Gui::SelectionSingleton::SubjectType &rCaller,
                  Gui::SelectionSingleton::MessageType Reason);

private Q_SLOTS:
    void on_changeMaterial_activated(int);
    void on_changeMode_activated(const QString&);
    void on_changePlot_activated(const QString&);
    void on_buttonColor_changed();
    void on_spinTransparency_valueChanged(int);
    void on_spinPointSize_valueChanged(int);
    void on_buttonLineColor_changed();
    void on_spinLineWidth_valueChanged(int);
    void on_spinLineTransparency_valueChanged(int);
    void on_buttonUserDefinedMaterial_clicked();
    void on_buttonColorPlot_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    void slotChangedObject(const Gui::ViewProvider&, const App::Property& Prop);
    void reject();
    void setDisplayModes(const std::vector<ViewProvider*>&);
    void setMaterial(const std::vector<ViewProvider*>&);
    void setColorPlot(const std::vector<ViewProvider*>&);
    void fillupMaterials();
    void setShapeColor(const std::vector<ViewProvider*>&);
    void setLineColor(const std::vector<ViewProvider*>&);
    void setPointSize(const std::vector<ViewProvider*>&);
    void setLineWidth(const std::vector<ViewProvider*>&);
    void setTransparency(const std::vector<ViewProvider*>&);
    void setLineTransparency(const std::vector<ViewProvider*>&);
    std::vector<ViewProvider*> getSelection() const;

    DlgDisplayPropertiesImp_Connection connectChangedObject;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGDISPLAYPROPERTIES_IMP_H
