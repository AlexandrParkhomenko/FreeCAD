/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef GUI_TEXTUREMAPPING_H
#define GUI_TEXTUREMAPPING_H

#include "stdexport.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"

class SoGroup;
class SoTexture2;
class SoTextureCoordinateEnvironment;

namespace Gui {
namespace Dialog {

class Ui_TextureMapping;
class GuiExport TextureMapping : public QDialog
{
    Q_OBJECT

public:
    TextureMapping(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~TextureMapping();
    void accept();
    void reject();

private Q_SLOTS:
    void on_fileChooser_fileNameSelected(const QString&);
    void on_checkEnv_toggled(bool);

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    SoGroup* grp;
    SoTexture2* tex;
    SoTextureCoordinateEnvironment* env;
    QString fileName;
    Ui_TextureMapping* ui;
};

class TaskTextureMapping : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskTextureMapping();
    ~TaskTextureMapping();

public:
    bool accept();
    bool reject();

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Close; }

private:
    TextureMapping* dialog;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_TEXTUREMAPPING_H
