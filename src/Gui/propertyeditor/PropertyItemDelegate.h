/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PROPERTYITEMDELEGATE_H
#define PROPERTYITEMDELEGATE_H

#include <QItemDelegate>

namespace Gui {
namespace PropertyEditor {

class PropertyItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    PropertyItemDelegate(QObject* parent);
    ~PropertyItemDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const;
    virtual QWidget * createEditor (QWidget *, const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex& index ) const;
    virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual bool editorEvent (QEvent *event, QAbstractItemModel *model,
                              const QStyleOptionViewItem& option, const QModelIndex& index);

public Q_SLOTS:
    void valueChanged();
    void editorClosed (QWidget * editor, QAbstractItemDelegate::EndEditHint hint);

private:
    mutable bool pressed;
};

} // namespace PropertyEditor
} // namespace Gui

#endif // PROPERTYITEMDELEGATE_H
