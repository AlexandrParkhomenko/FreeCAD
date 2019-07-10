/***************************************************************************
 *   Copyright (c) 2017 Kustaa Nyholm  <kustaa.nyholm@sparetimelabs.com>   *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef SRC_GUI_NAVICUBE_H_
#define SRC_GUI_NAVICUBE_H_

#include "stdexport.h"
#include <CXX/Extensions.hxx>

class SoEvent;

namespace Gui {
class View3DInventorViewer;
}

class NaviCubeImplementation;

class GuiExport NaviCube {
public:
	enum Corner {
		TopLeftCorner,
		TopRightCorner,
		BottomLeftCorner,
		BottomRightCorner
	};
	NaviCube(Gui::View3DInventorViewer* viewer) ;
	virtual ~NaviCube();
	void drawNaviCube();
	void createContextMenu(const std::vector<std::string>& cmd);
	bool processSoEvent(const SoEvent* ev);
	void setCorner(Corner);
	static void setNaviCubeCommands(const std::vector<std::string>& cmd);
	static void setNaviCubeLabels(const std::vector<std::string>& labels);
private:
	NaviCubeImplementation* m_NaviCubeImplementation;
};

class HuuhaaClassPy : public Py::PythonExtension<HuuhaaClassPy> {
public:
    Py::Object huuhaa(const Py::Tuple&);
	static void init_type() ;
};

#endif /* SRC_GUI_NAVICUBE_H_ */
