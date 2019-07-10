/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_PROPERTYEDITOR_MESH_H
#define MESHGUI_PROPERTYEDITOR_MESH_H

#include "stdexport.h"
#include "Gui/propertyeditor/PropertyItem.h"

namespace MeshGui {

/**
 * Display data of a mesh kernel.
 * \author Werner Mayer
 */
class MeshGuiExport PropertyMeshKernelItem : public Gui::PropertyEditor::PropertyItem
{
    Q_OBJECT
    Q_PROPERTY(int Points READ countPoints)
    Q_PROPERTY(int Edges READ countEdges)
    Q_PROPERTY(int Faces READ countFaces)
    PROPERTYITEM_HEADER

    virtual QWidget* createEditor(QWidget* parent, const QObject* receiver, const char* method) const;
    virtual void setEditorData(QWidget *editor, const QVariant& data) const;
    virtual QVariant editorData(QWidget *editor) const;

    int countPoints() const;
    int countEdges() const;
    int countFaces() const;

protected:
    virtual QVariant toolTip(const App::Property*) const;
    virtual QVariant value(const App::Property*) const;
    virtual void setValue(const QVariant&);

protected:
    PropertyMeshKernelItem();
    void initialize();

private:
    Gui::PropertyEditor::PropertyIntegerItem* m_p;
    Gui::PropertyEditor::PropertyIntegerItem* m_e;
    Gui::PropertyEditor::PropertyIntegerItem* m_f;
};

} // namespace MeshGui


#endif // MESHGUI_PROPERTYEDITOR_MESH_H

