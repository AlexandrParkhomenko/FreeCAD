/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGSIMAGE_IMP_H
#define GUI_DIALOG_DLGSETTINGSIMAGE_IMP_H

#include <Inventor/SoOffscreenRenderer.h> 
#include <Inventor/SbMatrix.h> 

#include "ui_DlgSettingsImage.h"

namespace Gui {
namespace Dialog {
/**
 * The DlgSettings3DViewImp class implements a preference page to change settings
 * for the Inventor viewer.
 * @author Werner Mayer
 */
class DlgSettingsImageImp : public QWidget, public Ui::DlgSettingsImage
{
    Q_OBJECT

public:
    DlgSettingsImageImp( QWidget* parent = 0 );
    ~DlgSettingsImageImp();

    /** @name Image dimensions */
    //@{
    void setImageSize( int, int );
    void setImageSize( const QSize& );
    QSize imageSize() const;
    int imageWidth() const;
    int imageHeight() const;
    //@}

    /** @name Image meta information */
    //@{
    QString comment() const;
    int backgroundType() const;
    void setBackgroundType( int );
    bool addWatermark() const;
    //@}

public Q_SLOTS:
    void onSelectedFilter( const QString& );

protected Q_SLOTS:
    void on_buttonRatioScreen_clicked();
    void on_buttonRatio4x3_clicked();
    void on_buttonRatio16x9_clicked();
    void on_buttonRatio1x1_clicked();
    void on_standardSizeBox_activated(int);

protected:
    // helper to force an aspect ratio
    void adjustImageSize(float fRatio);
    void changeEvent(QEvent *e);


private:
    float _fRatio;
    int _width, _height;
    SbMatrix _Matrix;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGSIMAGE_IMP_H
