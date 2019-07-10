/***************************************************************************
 *   Copyright (c) 2017 Peter Lama (peterldev94@gmail.com)                 *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_PropertyEnumAttacherItem_H
#define PART_PropertyEnumAttacherItem_H

#include "stdexport.h"
#include "Gui/propertyeditor/PropertyItem.h"
#include "TaskAttacher.h"

namespace PartGui
{

/**
* Custom editor item for PropertyEnumeration to open Attacher task
*/
class PartGuiExport PropertyEnumAttacherItem: public Gui::PropertyEditor::PropertyEnumItem
{
    Q_OBJECT

public:
    PROPERTYITEM_HEADER

    virtual QWidget* createEditor(QWidget* parent, const QObject* receiver, const char* method) const;
    virtual void setEditorData(QWidget* editor, const QVariant& data) const;
    virtual QVariant editorData(QWidget* editor) const;

protected Q_SLOTS:
    void openTask();

protected:
    PropertyEnumAttacherItem();
};

} // namespace PartGui

#endif // PART_PropertyEnumAttacherItem_H
