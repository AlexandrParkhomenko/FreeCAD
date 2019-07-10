/***************************************************************************
 *   Copyright (c) 2015 Eivind Kvedalen <eivind@kvedalen.name>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef GUI_DIALOG_DLGEXPRESSIONINPUT_H
#define GUI_DIALOG_DLGEXPRESSIONINPUT_H

#include "stdexport.h"
#include <QDialog>
#include "Base/Unit.h"
#include "App/ObjectIdentifier.h"
#include <boost/shared_ptr.hpp>

namespace Ui {
class DlgExpressionInput;
}

namespace Base {
class Quantity;
}

namespace App {
class Path;
class Expression;
class DocumentObject;
}

namespace Gui {

namespace Dialog {

class GuiExport DlgExpressionInput : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgExpressionInput(const App::ObjectIdentifier & _path, boost::shared_ptr<const App::Expression> _expression, const Base::Unit &_impliedUnit, QWidget *parent = 0);
    ~DlgExpressionInput();
    
    boost::shared_ptr<App::Expression> getExpression() const { return expression; }

    bool discardedFormula() const { return discarded; }

    QPoint expressionPosition() const;
    void   setExpressionInputSize(int width, int height);

    bool eventFilter(QObject *obj, QEvent *event);

protected:
    void showEvent(QShowEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

private Q_SLOTS:
    void textChanged(const QString & text);
    void setDiscarded();

private:
    ::Ui::DlgExpressionInput *ui;
    boost::shared_ptr<App::Expression> expression;
    App::ObjectIdentifier path;
    bool discarded;
    const Base::Unit impliedUnit;

    int minimumWidth;
};

}
}

#endif // GUI_DIALOG_EXPRESSIONINPUT_H
