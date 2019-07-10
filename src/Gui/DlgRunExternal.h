/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DlgRunExternal_H
#define GUI_DIALOG_DlgRunExternal_H

#include "stdexport.h"
#include <QProcess>
#include <QDialog>

namespace Gui {
namespace Dialog {
class Ui_DlgRunExternal;

/**
 * The DlgRunExternal class implements a dialog to start and control external
 * programs to edit FreeCAD controlled content.
 * \author Jürgen Riegel
 */
class GuiExport DlgRunExternal : public QDialog
{ 
    Q_OBJECT

public:
    DlgRunExternal(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    virtual ~DlgRunExternal();

    int Do(void);

    QString ProcName;
    QStringList arguments;

protected Q_SLOTS:
    virtual void reject(void);
    virtual void accept(void);
    virtual void abort(void);
    virtual void advanced(void);
    void finished (int exitCode, QProcess::ExitStatus exitStatus);
    void on_chooseProgram_clicked();

protected:
    QProcess process;
    bool advancedHidden;

private:
    Ui_DlgRunExternal* ui;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DlgRunExternal_H
