/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_NAMESPACE_H
#define GUI_NAMESPACE_H


namespace Gui {

enum SelectionRole {
    None = 0,
    Inner = 1,
    Outer = 2,
    Split = 3,
    Custom0 = 4,
    Custom1 = 5,
    Custom2 = 6,
};

} // namespace Gui

#endif // GUI_NAMESPACE_H
