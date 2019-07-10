
/***************************************************************************
* Copyright (c) 2014 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>        *
*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                          *
***************************************************************************/
#ifndef PROPERTYCONSTRAINTLISTITEM_H
#define PROPERTYCONSTRAINTLISTITEM_H

#include <QObject>
#include <QPointer>
#include <QItemEditorFactory>
#include <vector>
#include <QList>

#include "Base/Type.h"
#include "Base/Quantity.h"
#include "Base/UnitsApi.h"
#include "App/PropertyStandard.h"
#include "Gui/Widgets.h"

#include "Gui/propertyeditor/PropertyItem.h"


namespace SketcherGui {

class PropertyConstraintListItem: public Gui::PropertyEditor::PropertyItem
{
    Q_OBJECT
    PROPERTYITEM_HEADER

    virtual ~PropertyConstraintListItem();
    virtual void assignProperty(const App::Property* prop);
    virtual QWidget* createEditor(QWidget* parent, const QObject* receiver, const char* method) const;
    virtual void setEditorData(QWidget *editor, const QVariant& data) const;
    virtual QVariant editorData(QWidget *editor) const;

protected:
    virtual QVariant toString(const QVariant&) const;
    virtual QVariant value(const App::Property*) const;
    virtual void setValue(const QVariant&);
    virtual bool event (QEvent* ev);

    virtual void initialize();

protected:
    PropertyConstraintListItem();
    bool blockEvent;
    bool onlyUnnamed;
};

} //namespace SketcherGui


#endif
