/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGUNDOREDO_H
#define GUI_DIALOG_DLGUNDOREDO_H

#include <QMenu>

namespace Gui {
namespace Dialog {

/** This class implements the undo dialog.
 * \author Werner Mayer
 */
class UndoDialog : public QMenu
{ 
    Q_OBJECT

public:
  UndoDialog( QWidget* parent = 0 );
  virtual ~UndoDialog();

protected Q_SLOTS:
  void onSelected();
  void onFetchInfo();
};

/** This class implements the redo dialog.
 * \author Werner Mayer
 */
class RedoDialog : public QMenu
{ 
    Q_OBJECT

public:
  RedoDialog( QWidget* parent = 0 );
  virtual ~RedoDialog();

protected Q_SLOTS:
  void onSelected();
  void onFetchInfo();
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGUNDOREDO_H
