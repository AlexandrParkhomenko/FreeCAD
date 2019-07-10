/***************************************************************************
 *   Copyright (c) 2015 Eivind Kvedalen <eivind@kvedalen.name>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef QUANTITYSPINBOX_P_H
#define QUANTITYSPINBOX_P_H

#include <QLabel>

class ExpressionLabel : public QLabel
{
    Q_OBJECT
public:
    ExpressionLabel(QWidget * parent) : QLabel(parent) { }
protected:
    void mouseReleaseEvent(QMouseEvent * event) {
        if (rect().contains(event->pos()))
                Q_EMIT clicked();
    }

Q_SIGNALS:
    void clicked();
};

#endif // QUANTITYSPINBOX_P_H
