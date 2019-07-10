/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DEMOMODE_H
#define GUI_DIALOG_DEMOMODE_H

#include "stdexport.h"
#include <Inventor/SbLinear.h>
#include <QDialog>

class QTimer;
class SoCamera;
class SbRotation;

namespace Gui {
class View3DInventor;
namespace Dialog {

/**
 * @author Werner Mayer
 */
class Ui_DemoMode;
class GuiExport DemoMode : public QDialog
{
    Q_OBJECT

public:
    DemoMode(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DemoMode();

    void accept();
    void reject();

protected Q_SLOTS:
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_fullscreen_toggled(bool);
    void on_timerCheck_toggled(bool);
    void on_speedSlider_valueChanged(int);
    void on_angleSlider_valueChanged(int);
    void on_timeout_valueChanged(int);
    void onAutoPlay();

private:
    void reset();
    float getSpeed(int) const;
    void reorientCamera(SoCamera * cam, const SbRotation & rot);
    SbVec3f getDirection(Gui::View3DInventor*) const;
    Gui::View3DInventor* activeView() const;
    void startAnimation(Gui::View3DInventor*);
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *, QEvent *);
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    int oldvalue;
    SbVec3f viewAxis;
    bool wasHidden;
    QPoint pnt;
    QPoint oldPos;
    Ui_DemoMode* ui;
    QTimer* timer;
    QTimer* showHideTimer;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DEMOMODE_H
