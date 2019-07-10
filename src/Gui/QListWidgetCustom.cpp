/***************************************************************************
 *   Copyright (c) 2015 FreeCAD Developers                                 *
 *   Author: Przemo Firszt <przemo@firszt.eu>                              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

# include <QListWidget>
# include <QDragMoveEvent>
# include <QString>

#include "QListWidgetCustom.h" 

QListWidgetCustom::QListWidgetCustom(QWidget * parent)
  : QListWidget(parent)
{
}

QListWidgetCustom::~QListWidgetCustom()
{
}

/* Overridden dragMoveEvent prevents dragging items that originated
 * from the same list for "disabled workbenches". Dragging from outside
 * is still allowed. Also it blocks dragging from another instance of FreeCAD
 */
void QListWidgetCustom::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->source() != 0) {
        QVariant prop = this->property("OnlyAcceptFrom");
        if (prop.isValid()) {
            QStringList filter = prop.toStringList();
            QString sender = e->source()->objectName();
            if (!filter.contains(sender)) {
                e->ignore();
            } else {
                e->accept();
            }
        } else {
            e->accept();
        }
    } else {
        e->ignore();
    }
}

#include "moc_QListWidgetCustom.cpp"
