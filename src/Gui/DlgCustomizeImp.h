/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGCUSTOMIZE_IMP_H
#define GUI_DIALOG_DLGCUSTOMIZE_IMP_H

#include <QDialog>

class QTabWidget;
class QGridLayout;
class QHBoxLayout;

namespace Gui {
namespace Dialog {

/**
 * Dialog which contains several tab pages to customize
 * the changeable toolbars and commandbars or to define
 * own macro actions. 
 *
 * You can extend the existing toolbars or commandbars with 
 * several commands just by drag and drop.
 * @see DlgCustomCommandsImp
 * @see DlgCustomToolbarsImp
 * @see DlgCustomCmdbarsImp
 * @see DlgCustomActionsImp
 * \author Werner Mayer
 */
class DlgCustomizeImp : public QDialog
{ 
    Q_OBJECT

public:
    DlgCustomizeImp(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgCustomizeImp();

    static void addPage(const char* className);
    void addPage (QWidget* w);

Q_SIGNALS:
    void addMacroAction(const QByteArray&);
    void removeMacroAction(const QByteArray&);
    void modifyMacroAction(const QByteArray&);

protected:
    void changeEvent(QEvent *e);

private:
    /** @name for internal use only */
    //@{
    QPushButton* buttonHelp; /**< the help button */
    QPushButton* buttonClose; /**< the cancel button */
    QTabWidget* tabWidget; /**< tab wigdets containing all pages */ 
    QGridLayout* customLayout; /**< layout */
    QHBoxLayout* layout; /** horizontal layout */
    static QList<QByteArray> _pages; /**< Name of all registered preference pages */
    //@}
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGCUSTOMIZE_IMP_H
