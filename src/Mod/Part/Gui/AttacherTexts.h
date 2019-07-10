/***************************************************************************
 *   Copyright (c) Victor Titov (DeepSOIC)                                 *
 *                                           (vv.titov@gmail.com) 2016     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

/**
  * AttacherTexts.h, .cpp - files that contain user-friendly translatable names
  * of attachment modes, as well as help texts, and the like.
  */

#ifndef PARTATTACHERTEXTS_H
#define PARTATTACHERTEXTS_H

#include "stdexport.h"
#include <vector>
#include <QString>
#include <QStringList>
#include <CXX/Objects.hxx>
#include "Mod/Part/App/Attacher.h"


namespace AttacherGui {

typedef std::vector<QString> TextSet;

/**
 * @brief getUIStrings
 * @param attacherType
 * @param mmode
 * @return vector of two QStrings:
 * first is the name of attachment mode. e.g. "Tangent to surface";
 * second is tooltip-style explanation of the mode, like "Plane is tangent to a surface at vertex."
 */
TextSet PartGuiExport getUIStrings(Base::Type attacherType, Attacher::eMapMode mmode);


QString PartGuiExport getShapeTypeText(Attacher::eRefType type);

QStringList PartGuiExport getRefListForMode(Attacher::AttachEngine &attacher, Attacher::eMapMode mmode);


// Python interface
class PartGuiExport AttacherGuiPy{
public:
    static PyMethodDef    Methods[];
    static PyObject* sGetModeStrings(PyObject * /*self*/, PyObject *args);
    static PyObject* sGetRefTypeUserFriendlyName(PyObject * /*self*/, PyObject *args);
};

}
#endif
