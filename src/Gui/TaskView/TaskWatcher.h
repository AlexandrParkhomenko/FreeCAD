/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TASKWATCHER_H
#define GUI_TASKVIEW_TASKWATCHER_H

#include <map>
#include <string>
#include <vector>
#include <QObject>

#include "Gui/Selection.h"
#include "Gui/SelectionFilter.h"

namespace App {

}

namespace Gui {
namespace TaskView {

class TaskContent;

/// Father class of watcher classes
class GuiExport TaskWatcher : public QObject, public Gui::SelectionFilter
{
    Q_OBJECT

public:
    TaskWatcher(const char* Filter);
    virtual ~TaskWatcher();

    std::vector<QWidget*> &getWatcherContent(void);

public:
    /// is called wenn the document or the Selection changes. 
    virtual bool shouldShow(void);

protected:
    /// List of TaskBoxes of that dialog
    std::vector<QWidget*> Content;

};

// --------------------------------------------------------------------------

/// Special watcher class for showing commands dependene on the selection
class GuiExport TaskWatcherCommands : public TaskWatcher
{
    Q_OBJECT

public:
    TaskWatcherCommands(const char* Filter,const char* commands[], const char* name, const char* pixmap);

public:
    /// is called wenn the document or the Selection changes. 
    virtual bool shouldShow(void);

};

// --------------------------------------------------------------------------

/// Special watcher class for showing commands when active document is empty
class GuiExport TaskWatcherCommandsEmptyDoc : public TaskWatcherCommands
{
    Q_OBJECT

public:
    TaskWatcherCommandsEmptyDoc(const char* commands[], const char* name, const char* pixmap);

public:
    /// is called wenn the document or the Selection changes. 
    virtual bool shouldShow(void);

};

// --------------------------------------------------------------------------

/// Special watcher class for showing commands when there is nothing selected
class GuiExport TaskWatcherCommandsEmptySelection : public TaskWatcherCommands
{
    Q_OBJECT

public:
    TaskWatcherCommandsEmptySelection(const char* commands[], const char* name, const char* pixmap);
    ~TaskWatcherCommandsEmptySelection();

public:
    /// is called wenn the document or the Selection changes. 
    virtual bool shouldShow(void);

};



} //namespace TaskView
} //namespace Gui

#endif // GUI_TASKVIEW_TASKWATCHER_H
