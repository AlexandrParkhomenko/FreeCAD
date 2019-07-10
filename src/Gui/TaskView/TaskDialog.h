/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TASKDIALOG_H
#define GUI_TASKVIEW_TASKDIALOG_H

#include <map>
#include <string>
#include <vector>

#include <QDialogButtonBox>

#include "Gui/Selection.h"

namespace App {

}

namespace Gui {
namespace TaskView {

class TaskContent;

/// Father class of content with header and Icon
class GuiExport TaskDialog : public QObject
{
    Q_OBJECT

public:
    enum ButtonPosition {
        North, South
    };

    TaskDialog();
    ~TaskDialog();

    void setButtonPosition(ButtonPosition p)
    { pos = p; }
    ButtonPosition buttonPosition() const
    { return pos; }
    const std::vector<QWidget*> &getDialogContent(void) const;
    bool canClose() const;

    /// tells the framework which buttons are wished for the dialog
    virtual QDialogButtonBox::StandardButtons getStandardButtons(void) const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }
    virtual void modifyStandardButtons(QDialogButtonBox*)
    {}

    const std::string& getDocumentName() const
    { return documentName; }
    void setDocumentName(const std::string& doc)
    { documentName = doc; }
    /*!
      Indicates whether this task dialog allows other commands to modify
      the document while it is open.
    */
    virtual bool isAllowedAlterDocument(void) const
    { return false; }
    /*!
      Indicates whether this task dialog allows other commands to modify
      the 3d view while it is open.
    */
    virtual bool isAllowedAlterView(void) const
    { return true; }
    /*!
      Indicates whether this task dialog allows other commands to modify
      the selection while it is open.
    */
    virtual bool isAllowedAlterSelection(void) const
    { return true; }
    virtual bool needsFullSpace() const
    { return false; }

public:
    /// is called by the framework when the dialog is opened
    virtual void open();
    /// is called by the framework if a button is clicked which has no accept or reject role
    virtual void clicked(int);
    /// is called by the framework if the dialog is accepted (Ok)
    virtual bool accept();
    /// is called by the framework if the dialog is rejected (Cancel)
    virtual bool reject();
    /// is called by the framework if the user press the help button 
    virtual void helpRequested();

    void emitDestructionSignal() {
        Q_EMIT aboutToBeDestroyed();
    }
    
Q_SIGNALS:
    void aboutToBeDestroyed();
    
protected:
    /// List of TaskBoxes of that dialog
    std::vector<QWidget*> Content;
    ButtonPosition pos;

private:
    std::string documentName;
};

} //namespace TaskView
} //namespace Gui

#endif // GUI_TASKVIEW_TASKDIALOG_H
