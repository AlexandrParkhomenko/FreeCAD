/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_INVENTOR_MARKERBITMAPS_H
#define GUI_INVENTOR_MARKERBITMAPS_H

#include "stdexport.h"
#include <string>
#include <list>
#include <map>

namespace Gui { namespace Inventor {

class GuiExport MarkerBitmaps {

public:
    static void initClass();
    static int getMarkerIndex(const std::string&, int px);
    static std::list<int> getSupportedSizes(const std::string&);

private:
    static void createBitmap(const std::string&, int px, int width, int height, const char* marker);

private:
    typedef std::pair<std::string, int> Marker;
    static std::map<Marker, int> markerIndex;
};

} // namespace Inventor

} // namespace Gui

#endif // GUI_INVENTOR_MARKERBITMAPS_H

