/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGINPUTDIALOGIMP_H
#define GUI_DIALOG_DLGINPUTDIALOGIMP_H

#include "stdexport.h"
#include "ui_DlgInputDialog.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgInputDialogImp dialog class does basically the same as Qt's QInputDialog
 * unless that it provides no static function but the application programmer must
 * create an instance and prepare it. This requires a little more work but increases
 * the flexibility.
 * \author Werner Mayer
 */
class GuiExport DlgInputDialogImp : public QDialog, public Ui_DlgInputDialog
{
  Q_OBJECT

public:
  enum Type { LineEdit, SpinBox, UIntBox, FloatSpinBox, ComboBox };

  DlgInputDialogImp( const QString& label, QWidget* parent = 0, bool modal = true, Type = LineEdit );
  ~DlgInputDialogImp();

  void setType( Type t );
  Type type() const;

  QSpinBox *getSpinBox() const;
  Gui::UIntSpinBox *getUIntBox() const;
  QDoubleSpinBox *getFloatSpinBox() const;
  QLineEdit *getLineEdit() const;
  QComboBox *getComboBox() const;

protected Q_SLOTS:
  void textChanged( const QString &s );
  void tryAccept();

protected:
  Type inputtype;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGINPUTDIALOGIMP_H
