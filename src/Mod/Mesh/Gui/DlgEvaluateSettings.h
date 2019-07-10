/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_DLG_EVALUATE_SETTINGS_H
#define MESHGUI_DLG_EVALUATE_SETTINGS_H

#include <QDialog>

namespace MeshGui {

class Ui_DlgEvaluateSettings;

/**
 * \author Werner Mayer
 */
class DlgEvaluateSettings : public QDialog
{
    Q_OBJECT

public:
    DlgEvaluateSettings(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgEvaluateSettings();

    void setNonmanifoldPointsChecked(bool);
    bool isNonmanifoldPointsChecked() const;

    void setFoldsChecked(bool);
    bool isFoldsChecked() const;

    void setDegeneratedFacetsChecked(bool);
    bool isDegeneratedFacetsChecked() const;

private:
    Ui_DlgEvaluateSettings* ui;
};

} // namespace MeshGui

#endif // MESHGUI_DLG_EVALUATE_SETTINGS_H
