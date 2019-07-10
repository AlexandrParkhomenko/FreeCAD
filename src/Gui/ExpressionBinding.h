/***************************************************************************
 *   Copyright (c) 2015 Eivind Kvedalen <eivind@kvedalen.name>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef EXPRESSIONBINDING_H
#define EXPRESSIONBINDING_H

#include "stdexport.h"
#include <string>
#include "App/ObjectIdentifier.h"
#include <boost/shared_ptr.hpp>
#include <QLabel>
#include <boost/signals2.hpp>

namespace App {
class Expression;
}

namespace Gui {

class GuiExport ExpressionBinding
{
public:
    ExpressionBinding();
    ~ExpressionBinding();

    virtual void bind(const App::ObjectIdentifier & _path);
    virtual void bind(const App::Property & prop);
    bool isBound() const;
    virtual bool apply(const std::string &propName);
    virtual bool apply();
    bool hasExpression() const;

    QPixmap getIcon(const char *name, const QSize &size) const;
   
    //auto apply means that the python code is issued not only on apply() but 
    //also on setExpression
    bool autoApply() const {return m_autoApply;};
    void setAutoApply(bool value) {m_autoApply = value;};
    
protected:
    const App::ObjectIdentifier & getPath() const { return path; }
    boost::shared_ptr<App::Expression> getExpression() const;
    std::string getExpressionString() const;
    std::string getEscapedExpressionString() const;
    virtual void setExpression(boost::shared_ptr<App::Expression> expr);
    
    //gets called when the bound expression is changed, either by this binding or any external action
    virtual void onChange() {};

private:
    App::ObjectIdentifier path;
    boost::shared_ptr<App::Expression> lastExpression;

protected:
    QLabel* iconLabel;
    QPalette defaultPalette;
    int iconHeight;

    void expressionChange(const App::ObjectIdentifier& id);
    boost::signals2::scoped_connection connection;
    bool m_autoApply;
};

}

#endif // EXPRESSIONBINDING_H
