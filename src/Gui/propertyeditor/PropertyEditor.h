/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <map>
#include <string>
#include <vector>

#include <QTreeView>

#include "PropertyItem.h"
#include "PropertyModel.h"

namespace App {
class Property;
}

namespace Gui {
namespace PropertyEditor {

class PropertyModel;
/*!
 Put this into the .qss file after Gui--PropertyEditor--PropertyEditor
 
 Gui--PropertyEditor--PropertyEditor
 {
    qproperty-groupBackground: gray;
    qproperty-groupTextColor: white;
 }

 See also: https://man42.net/blog/2011/09/qt-4-7-modify-a-custom-q_property-with-a-qt-style-sheet/

*/

class PropertyEditor : public QTreeView
{
    Q_OBJECT

    Q_PROPERTY(QBrush groupBackground READ groupBackground WRITE setGroupBackground DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor groupTextColor READ groupTextColor WRITE setGroupTextColor DESIGNABLE true SCRIPTABLE true)

public:
    PropertyEditor(QWidget *parent = 0);
    ~PropertyEditor();

    /** Builds up the list view with the properties. */
    void buildUp(const PropertyModel::PropertyList& props);
    void updateProperty(const App::Property&);
    void updateEditorMode(const App::Property&);
    void appendProperty(const App::Property&);
    void removeProperty(const App::Property&);
    void setAutomaticDocumentUpdate(bool);
    bool isAutomaticDocumentUpdate(bool) const;
    /*! Reset the internal state of the view. */
    virtual void reset();

    QBrush groupBackground() const;
    void setGroupBackground(const QBrush& c);
    QColor groupTextColor() const;
    void setGroupTextColor(const QColor& c);

public Q_SLOTS:
    void onItemActivated(const QModelIndex &index);

protected:
    virtual void closeEditor (QWidget * editor, QAbstractItemDelegate::EndEditHint hint);
    virtual void commitData (QWidget * editor);
    virtual void editorDestroyed (QObject * editor);
    virtual void currentChanged (const QModelIndex & current, const QModelIndex & previous);
    virtual void rowsInserted (const QModelIndex & parent, int start, int end);
    virtual void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
    virtual QStyleOptionViewItem viewOptions() const;
    virtual bool event(QEvent*);

private:
    void setEditorMode(const QModelIndex & parent, int start, int end);
    void updateItemEditor(bool enable, int column, const QModelIndex& parent);

private:
    PropertyModel* propertyModel;
    QStringList selectedProperty;
    PropertyModel::PropertyList propList;
    bool autoupdate;
    bool committing;
    bool delaybuild;
    QColor groupColor;
    QBrush background;
};

} //namespace PropertyEditor
} //namespace Gui

#endif // PROPERTYEDITOR_H
