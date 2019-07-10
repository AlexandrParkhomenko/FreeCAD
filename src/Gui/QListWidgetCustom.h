/***************************************************************************
 *   Copyright (c) 2015 FreeCAD Developers                                 *
 *   Author: Przemo Firszt <przemo@firszt.eu>                              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef QLISTWIDGETCUSTOM_HPP
#define QLISTWIDGETCUSTOM_HPP

#include <QListWidget>
#include <QDragMoveEvent>
#include <QString>

class QListWidgetCustom : public QListWidget
{
    Q_OBJECT

public:
    QListWidgetCustom (QWidget *parent);
    virtual ~QListWidgetCustom ();

protected:
    void dragMoveEvent(QDragMoveEvent *e);
};

#endif
