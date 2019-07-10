/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef GUI_METATYPES_H
#define GUI_METATYPES_H

#include "Base/Vector3D.h"
#include "Base/Matrix.h"
#include "Base/Placement.h"
#include "Base/Quantity.h"

Q_DECLARE_METATYPE(Base::Vector3f)
Q_DECLARE_METATYPE(Base::Vector3d)
Q_DECLARE_METATYPE(Base::Matrix4D)
Q_DECLARE_METATYPE(Base::Placement)
Q_DECLARE_METATYPE(Base::Quantity)
Q_DECLARE_METATYPE(QList<Base::Quantity>)

#endif // GUI_METATYPES_H
