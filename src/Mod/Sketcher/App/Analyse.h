/***************************************************************************
 *   Copyright (c) 2018 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef SKETCHER_ANALYSE_H
#define SKETCHER_ANALYSE_H

#include <vector>
#include "Mod/Sketcher/App/Constraint.h"

namespace Sketcher {

struct ConstraintIds {
        Base::Vector3d v;
        int First;
        int Second;
        Sketcher::PointPos FirstPos;
        Sketcher::PointPos SecondPos;
        Sketcher::ConstraintType Type;
};

struct Constraint_Equal  : public std::unary_function<const struct Sketcher::ConstraintIds&, bool>
{
    struct Sketcher::ConstraintIds c;
    Constraint_Equal(const ConstraintIds& c) : c(c)
    {
    }
    bool operator()(const ConstraintIds& x) const
    {
        if (c.First == x.First && c.FirstPos == x.FirstPos &&
            c.Second == x.Second && c.SecondPos == x.SecondPos)
            return true;
        if (c.Second == x.First && c.SecondPos == x.FirstPos &&
            c.First == x.Second && c.FirstPos == x.SecondPos)
            return true;
        return false;
    }
};

} //namespace Sketcher

#endif // SKETCHER_ANALYSE_H
