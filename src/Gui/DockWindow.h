/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DOCKWINDOW_H
#define GUI_DOCKWINDOW_H


#include "stdexport.h"
#include "Base/Parameter.h"
#include "Gui/View.h"
#include <QWidget>

namespace Gui {
class MDIView;
class Application;

/** Base class of all dockable windows belonging to a document
 *  there are two ways of belonging to a document. The 
 *  first way is to a fixed one. The second way is to always
 *  belong to the active document, that means switching every time
 *  the active document is changing. It also means that the view 
 *  belongs sometimes to no document at all!
 *  @see TreeView
 *  @see Gui::Document
 *  @see Application
 *  @author Jürgen Riegel
 */
class GuiExport DockWindow : public QWidget, public BaseView
{
  Q_OBJECT

public:
  /** View constructor
   * Attach the view to the given document. If the document is 0
   * the view will attach to the active document. Be aware there isn't
   * always an active document available!
   */
  DockWindow ( Gui::Document* pcDocument=0, QWidget *parent=0 );
  /** View destructor
   * Detach the view from the document, if attached.
   */
  virtual ~DockWindow();

  /** @name methods to override 
   */
  //@{
  /// get called when the document is updated
  virtual void onUpdate(void){}
  /// returns the name of the view (important for messages)
  virtual const char *getName(void) const { return "DockWindow"; }
  /// Message handler
  virtual bool onMsg(const char* ,const char** ){ return false; }
  /// Message handler test
  virtual bool onHasMsg(const char*) const { return false; }
  /// overwrite when checking on close state
  virtual bool canClose(void){return true;}
  //@}

Q_SIGNALS:
  /// sends a message to the document
  void sendCloseView(MDIView* theView);
};

} // namespace Gui

#endif // GUI_DOCKWINDOW_H 
