/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGSCOLORGRADIENT_IMP_H
#define GUI_DIALOG_DLGSETTINGSCOLORGRADIENT_IMP_H

#include "ui_DlgSettingsColorGradient.h"
#include "App/ColorModel.h"

class QDoubleValidator;

namespace Gui {
namespace Dialog {
/**
 * The DlgSettingsColorGradientImp class implements a preference page to change settings
 * for the color gradient bar.
 * @author Werner Mayer
 */
class DlgSettingsColorGradientImp : public QDialog, public Ui_DlgSettingsColorGradient
{
    Q_OBJECT

public:
    DlgSettingsColorGradientImp( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~DlgSettingsColorGradientImp();

    void accept();

    /** @name Color model */
    //@{
    void setColorModel( App::ColorGradient::TColorModel tModel);
    App::ColorGradient::TColorModel colorModel() const;
    //@}
    /** @name Color style */
    //@{
    void setColorStyle( App::ColorGradient::TStyle tStyle );
    App::ColorGradient::TStyle colorStyle() const;
    //@}
    /** @name Display mode */
    //@{
    void setOutGrayed( bool grayed );
    bool isOutGrayed() const;
    void setOutInvisible( bool invisible );
    bool isOutInvisible() const;
    //@}
    /** @name Parameter range and scale */
    //@{
    void setRange( float fMin, float fMax );
    void getRange( float& fMin, float& fMax) const;
    void setNumberOfLabels(int);
    int numberOfLabels() const;
    void setNumberOfDecimals(int);
    int numberOfDecimals() const;
    //@}

private:
    QDoubleValidator* fMaxVal;
    QDoubleValidator* fMinVal;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGSCOLORGRADIENT_IMP_H
