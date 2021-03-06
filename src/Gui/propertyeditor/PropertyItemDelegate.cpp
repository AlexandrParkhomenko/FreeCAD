/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QApplication>
# include <QModelIndex>
# include <QPainter>

#include "PropertyItemDelegate.h"
#include "PropertyItem.h"

using namespace Gui::PropertyEditor;


PropertyItemDelegate::PropertyItemDelegate(QObject* parent)
    : QItemDelegate(parent), pressed(false)
{
    connect(this, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)),
            this, SLOT(editorClosed(QWidget*, QAbstractItemDelegate::EndEditHint)));
}

PropertyItemDelegate::~PropertyItemDelegate()
{
}

QSize PropertyItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QSize size = QItemDelegate::sizeHint(option, index);
    size += QSize(0, 5);
    return size;
}

void PropertyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
    QStyleOptionViewItem option = opt;

    PropertyItem *property = static_cast<PropertyItem*>(index.internalPointer());

    if (property && property->isSeparator()) {
        QColor color = option.palette.color(QPalette::BrightText);
        QObject* par = parent();
        if (par) {
            QVariant value = par->property("groupTextColor");
            if (value.canConvert<QColor>())
                color = value.value<QColor>();
        }
        option.palette.setColor(QPalette::Text, color);
        option.font.setBold(true);
        option.state &= ~QStyle::State_Selected;
    }

    if (index.column() == 1) {
        option.state &= ~QStyle::State_Selected;
    }

    option.state &= ~QStyle::State_HasFocus;

    if (property && property->isSeparator()) {
        QBrush brush = option.palette.dark();
        QObject* par = parent();
        if (par) {
            QVariant value = par->property("groupBackground");
            if (value.canConvert<QBrush>())
                brush = value.value<QBrush>();
        }
        painter->fillRect(option.rect, brush);
    }

    QPen savedPen = painter->pen();

    QItemDelegate::paint(painter, option, index);

    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt, qobject_cast<QWidget*>(parent())));
    painter->setPen(QPen(color));
    if (index.column() == 1 || !(property && property->isSeparator())) {
        int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
        painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
    }
    painter->drawLine(option.rect.x(), option.rect.bottom(),
            option.rect.right(), option.rect.bottom());
    painter->setPen(savedPen);
}

bool PropertyItemDelegate::editorEvent (QEvent * event, QAbstractItemModel* model,
                                        const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (event && event->type() == QEvent::MouseButtonPress)
        this->pressed = true;
    else
        this->pressed = false;
    return QItemDelegate::editorEvent(event, model, option, index);
}

void PropertyItemDelegate::editorClosed(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    // don't close the editor when pressing Tab or Shift+Tab
    // https://forum.freecadweb.org/viewtopic.php?f=3&t=34627#p290957
    if (hint != EditNextItem && hint != EditPreviousItem)
        editor->close();
}

QWidget * PropertyItemDelegate::createEditor (QWidget * parent, const QStyleOptionViewItem & /*option*/, 
                                              const QModelIndex & index ) const
{
    if (!index.isValid())
        return 0;

    PropertyItem *childItem = static_cast<PropertyItem*>(index.internalPointer());
    if (!childItem)
        return 0;
    QWidget* editor = childItem->createEditor(parent, this, SLOT(valueChanged()));
    if (editor) // Make sure the editor background is painted so the cell content doesn't show through
        editor->setAutoFillBackground(true);
    if (editor && childItem->isReadOnly())
        editor->setDisabled(true);
    else if (editor /*&& this->pressed*/) {
        // We changed the way editor is activated in PropertyEditor (in response
        // of signal activated and clicked), so now we should grab focus
        // regardless of "pressed" or not (e.g. when activated by keyboard
        // enter)
        editor->setFocus();
    }
    this->pressed = false;
    return editor;
}

void PropertyItemDelegate::valueChanged()
{
    QWidget* editor = qobject_cast<QWidget*>(sender());
    if (editor)
        commitData(editor);
}

void PropertyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid())
        return;
    QVariant data = index.data(Qt::EditRole);
    PropertyItem *childItem = static_cast<PropertyItem*>(index.internalPointer());
    editor->blockSignals(true);
    childItem->setEditorData(editor, data);
    editor->blockSignals(false);
    return;
}

void PropertyItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (!index.isValid())
        return;
    PropertyItem *childItem = static_cast<PropertyItem*>(index.internalPointer());
    QVariant data = childItem->editorData(editor);
    model->setData(index, data, Qt::EditRole);
}

#include "moc_PropertyItemDelegate.cpp"
