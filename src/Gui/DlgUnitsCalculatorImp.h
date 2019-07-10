/***************************************************************************
 *   Copyright (c) 2013 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DlgActivateWindowImp_H
#define GUI_DIALOG_DlgActivateWindowImp_H

#include <QDialog>
#include <memory>
#include "Base/Quantity.h"
#include "Base/Unit.h"

namespace Gui {
namespace Dialog {
class Ui_DlgUnitCalculator;

/**
 * The DlgUnitsCalculator provides a unit conversion dialog
 * \author Juergen Riegel 
 */
class DlgUnitsCalculator : public QDialog
{
    Q_OBJECT

public:
    DlgUnitsCalculator(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgUnitsCalculator();

protected:
    void accept();
    void reject();

protected Q_SLOTS:
    void unitValueChanged(const Base::Quantity&);
    void valueChanged(const Base::Quantity&);
    void on_unitsBox_activated(int);

    void copy(void);
    void help(void);
    void returnPressed(void);

    void parseError(const QString& errorText);

private:
    Base::Quantity actValue;
    Base::Quantity actUnit;
    std::unique_ptr<Ui_DlgUnitCalculator> ui;
    QList<Base::Unit> units;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DlgActivateWindowImp_H
