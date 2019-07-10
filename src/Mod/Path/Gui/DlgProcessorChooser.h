/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PATH_DlgProcessorChooser_H
#define PATH_DlgProcessorChooser_H

#include <QDialog>
#include <QString>
#include "App/DocumentObject.h"

class Ui_DlgProcessorChooser;

namespace PathGui {

class DlgProcessorChooser : public QDialog
{
    Q_OBJECT

public:
    DlgProcessorChooser(std::vector<std::string> &scriptnames, bool withArguments = false);
    ~DlgProcessorChooser();

    std::string getProcessor();
    std::string getArguments();

    void accept();

protected Q_SLOTS:

private:
    Ui_DlgProcessorChooser* ui;
    std::string processor, arguments;
};

}

#endif // PATH_DlgProcessorChooser_H
