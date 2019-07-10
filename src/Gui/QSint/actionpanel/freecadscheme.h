/***************************************************************************
 *   Copyright (c) 2015 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef FREECADTASKPANELSCHEME_H
#define FREECADTASKPANELSCHEME_H

#include "actionpanelscheme.h"


namespace QSint
{


class QSINT_EXPORT FreeCADPanelScheme : public ActionPanelScheme
{
public:
    explicit FreeCADPanelScheme();

    static ActionPanelScheme* defaultScheme()
    {
        static FreeCADPanelScheme scheme;
        return &scheme;
    }

    void clearActionStyle();
    void restoreActionStyle();

private:
    QString builtinScheme;
    QString minimumStyle;
    QPixmap builtinFold;
    QPixmap builtinFoldOver;
    QPixmap builtinUnfold;
    QPixmap builtinUnfoldOver;
};

class QSINT_EXPORT SystemPanelScheme : public ActionPanelScheme
{
public:
    explicit SystemPanelScheme();

    static ActionPanelScheme* defaultScheme()
    {
        static SystemPanelScheme scheme;
        return &scheme;
    }

private:
    QPixmap drawFoldIcon(const QPalette& p, bool fold) const;
    QString systemStyle(const QPalette& p) const;
};

}

#endif // IISFREECADTASKPANELSCHEME_H
