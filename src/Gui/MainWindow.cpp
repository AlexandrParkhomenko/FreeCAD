/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


# include <algorithm>
# include <QApplication>
# include <QBuffer>
# include <QByteArray>
# include <QClipboard>
# include <QMimeData>
# include <QCloseEvent>
# include <QContextMenuEvent>
# include <QDesktopServices>
# include <QDesktopWidget>
# include <QDockWidget>
# include <QFontMetrics>
# include <QKeySequence>
# include <QLabel>
# include <QMdiSubWindow>
# include <QMessageBox>
# include <QPainter>
# include <QSettings>
# include <QSignalMapper>
# include <QStatusBar>
# include <QTimer>
# include <QToolBar>

#include <boost/bind.hpp>

// FreeCAD Base header
#include "Base/Parameter.h"
#include "Base/Exception.h"
#include "Base/FileInfo.h"
#include "Base/Interpreter.h"
#include "Base/Persistence.h"
#include "Base/Stream.h"
#include "Base/Reader.h"
#include "Base/Writer.h"
#include "App/Application.h"
#include "App/DocumentObject.h"
#include "App/DocumentObjectGroup.h"

#include "MainWindow.h"
#include "Application.h"
#include "WaitCursor.h"

#include "Action.h"
#include "Command.h"

#include "ToolBoxManager.h"
#include "DockWindowManager.h"
#include "ToolBarManager.h"
#include "WorkbenchManager.h"
#include "Workbench.h"

#include "Window.h" 
#include "View.h"
#include "Macro.h"
#include "ProgressBar.h"

#include "WidgetFactory.h"
#include "BitmapFactory.h"

#include "Tree.h"
#include "PropertyView.h"
#include "SelectionView.h"
#include "MenuManager.h"
#include "ReportView.h"
#include "CombiView.h"
#include "PythonConsole.h"
#include "TaskView/TaskView.h"
#include "DAGView/DAGView.h"

#include "DlgUndoRedo.h"
#include "DlgOnlineHelpImp.h"

#include "GuiInitScript.h"

#include "Document.h"
#include "MergeDocuments.h"
#include "ViewProviderExtern.h"

#include "View3DInventor.h"
#include "View3DInventorViewer.h"

using namespace Gui;
using namespace Gui::DockWnd;
using namespace std;


MainWindow* MainWindow::instance = 0L;

namespace Gui {

// Pimpl class
struct MainWindowP
{
    QLabel* sizeLabel;
    QLabel* actionLabel;
    QTimer* actionTimer;
    QTimer* activityTimer;
    QTimer* visibleTimer;
    QMdiArea* mdiArea;
    QPointer<MDIView> activeView;
    QSignalMapper* windowMapper;
    StatusBarObserver* status;
    QString whatstext;
    //#    QMap<QString, QPointer<UrlHandler> > urlHandler;
};

class MDITabbar : public QTabBar
{
public:
    MDITabbar( QWidget * parent = 0 ) : QTabBar(parent)
    {
        menu = new QMenu(this);
        // For Qt 4.2.x the tabs might be very wide
        setDrawBase(false);
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    }

    ~MDITabbar()
    {
        delete menu;
    }

protected:
    void contextMenuEvent ( QContextMenuEvent * e )
    {
        menu->clear();
        CommandManager& cMgr = Application::Instance->commandManager();
        if (tabRect(currentIndex()).contains(e->pos()))
            cMgr.getCommandByName("Std_CloseActiveWindow")->addTo(menu);
        cMgr.getCommandByName("Std_CloseAllWindows")->addTo(menu);
        menu->addSeparator();
        cMgr.getCommandByName("Std_CascadeWindows")->addTo(menu);
        cMgr.getCommandByName("Std_ArrangeIcons")->addTo(menu);
        cMgr.getCommandByName("Std_TileWindows")->addTo(menu);
        menu->addSeparator();
        cMgr.getCommandByName("Std_Windows")->addTo(menu);
        menu->popup(e->globalPos());
    }

private:
    QMenu* menu;
};

#if defined(Q_OS_WIN32)
class MainWindowTabBar : public QTabBar
{
public:
    MainWindowTabBar(QWidget *parent) : QTabBar(parent)
    {
        setExpanding(false);
    }
protected:
    bool event(QEvent *e)
    {
        // show the tooltip if tab is too small to fit label
        if (e->type() != QEvent::ToolTip)
            return QTabBar::event(e);
        QSize size = this->size();
        QSize hint = sizeHint();
        if (shape() == QTabBar::RoundedWest || shape() == QTabBar::RoundedEast) {
            size.transpose();
            hint.transpose();
        }
        if (size.width() < hint.width())
            return QTabBar::event(e);
        e->accept();
        return true;
    }
    void tabInserted (int index)
    {
        // get all dock windows
        QList<QDockWidget*> dw = getMainWindow()->findChildren<QDockWidget*>();
        for (QList<QDockWidget*>::iterator it = dw.begin(); it != dw.end(); ++it) {
            // compare tab text and window title to get the right dock window
            if (this->tabText(index) == (*it)->windowTitle()) {
                QWidget* dock = (*it)->widget();
                if (dock) {
                    QIcon icon = dock->windowIcon();
                    if (!icon.isNull())
                        setTabIcon(index, icon);
                }
                break;
            }
        }
    }
};
#endif

} // namespace Gui


/* TRANSLATOR Gui::MainWindow */

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags f)
  : QMainWindow( parent, f/*WDestructiveClose*/ )
{
    d = new MainWindowP;
    d->activeView = 0;

    // global access 
    instance = this;

    // Create the layout containing the workspace and a tab bar
    d->mdiArea = new QMdiArea();
    d->mdiArea->setTabPosition(QTabWidget::South);
    d->mdiArea->setViewMode(QMdiArea::TabbedView);
    QTabBar* tab = d->mdiArea->findChild<QTabBar*>();
    if (tab) {
        tab->setTabsClosable(true);
        // The tabs might be very wide
        tab->setExpanding(false);
    }
    d->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    d->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    d->mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, false);
    d->mdiArea->setActivationOrder(QMdiArea::ActivationHistoryOrder);
    d->mdiArea->setBackground(QBrush(QColor(160,160,160)));
    setCentralWidget(d->mdiArea);

    // labels and progressbar
    d->status = new StatusBarObserver();
    d->actionLabel = new QLabel(statusBar());
    // d->actionLabel->setMinimumWidth(120);
    d->sizeLabel = new QLabel(tr("Dimension"), statusBar());
    d->sizeLabel->setMinimumWidth(120);
    statusBar()->addWidget(d->actionLabel, 1);
    QProgressBar* progressBar = Gui::Sequencer::instance()->getProgressBar(statusBar());
    statusBar()->addPermanentWidget(progressBar, 0);
    statusBar()->addPermanentWidget(d->sizeLabel, 0);

    // clears the action label
    d->actionTimer = new QTimer( this );
    d->actionTimer->setObjectName(QString::fromLatin1("actionTimer"));
    connect(d->actionTimer, SIGNAL(timeout()), d->actionLabel, SLOT(clear()));

    // update gui timer
    d->activityTimer = new QTimer(this);
    d->activityTimer->setObjectName(QString::fromLatin1("activityTimer"));
    connect(d->activityTimer, SIGNAL(timeout()),this, SLOT(updateActions()));
    d->activityTimer->setSingleShot(false);
    d->activityTimer->start(300);

    // show main window timer
    d->visibleTimer = new QTimer(this);
    d->visibleTimer->setObjectName(QString::fromLatin1("visibleTimer"));
//    connect(d->visibleTimer, SIGNAL(timeout()),this, SLOT(showMainWindow()));
    d->visibleTimer->setSingleShot(true);

    d->windowMapper = new QSignalMapper(this);

    // connection between workspace, window menu and tab bar
    connect(d->windowMapper, SIGNAL(mapped(QWidget *)),
            this, SLOT(onSetActiveSubWindow(QWidget*)));
    connect(d->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(onWindowActivated(QMdiSubWindow* )));

    DockWindowManager* pDockMgr = DockWindowManager::instance();

    std::string hiddenDockWindows;;
    const std::map<std::string,std::string>& config = App::Application::Config();
    std::map<std::string, std::string>::const_iterator ht = config.find("HiddenDockWindow");
    if (ht != config.end())
        hiddenDockWindows = ht->second;

    // Tree view
    if (hiddenDockWindows.find("Std_TreeView") == std::string::npos) {
        //work through parameter.
        ParameterGrp::handle group = App::GetApplication().GetUserParameter().
              GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("DockWindows")->GetGroup("TreeView");
        bool enabled = group->GetBool("Enabled", true);
        group->SetBool("Enabled", enabled); //ensure entry exists.
        if (enabled) {
            TreeDockWidget* tree = new TreeDockWidget(0, this);
            tree->setObjectName
                (QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","Tree view")));
            tree->setMinimumWidth(210);
            pDockMgr->registerDockWindow("Std_TreeView", tree);
        }
    }

    // Property view
    if (hiddenDockWindows.find("Std_PropertyView") == std::string::npos) {
        //work through parameter.
        ParameterGrp::handle group = App::GetApplication().GetUserParameter().
              GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("DockWindows")->GetGroup("PropertyView");
        bool enabled = group->GetBool("Enabled", true);
        group->SetBool("Enabled", enabled); //ensure entry exists.
        if (enabled) {
            PropertyDockView* pcPropView = new PropertyDockView(0, this);
            pcPropView->setObjectName
                (QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","Property view")));
            pcPropView->setMinimumWidth(210);
            pDockMgr->registerDockWindow("Std_PropertyView", pcPropView);
        }
    }

    // Selection view
    if (hiddenDockWindows.find("Std_SelectionView") == std::string::npos) {
        SelectionView* pcSelectionView = new SelectionView(0, this);
        pcSelectionView->setObjectName
            (QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","Selection view")));
        pcSelectionView->setMinimumWidth(210);
        pDockMgr->registerDockWindow("Std_SelectionView", pcSelectionView);
    }

    // Combo view
    if (hiddenDockWindows.find("Std_CombiView") == std::string::npos) {
        CombiView* pcCombiView = new CombiView(0, this);
        pcCombiView->setObjectName(QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","Combo View")));
        pcCombiView->setMinimumWidth(150);
        pDockMgr->registerDockWindow("Std_CombiView", pcCombiView);
    }

    // Report view (must be created before PythonConsole!)
    if (hiddenDockWindows.find("Std_ReportView") == std::string::npos) {
        ReportOutput* pcReport = new ReportOutput(this);
        pcReport->setWindowIcon(BitmapFactory().pixmap("MacroEditor"));
        pcReport->setObjectName
            (QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","Report view")));
        pDockMgr->registerDockWindow("Std_ReportView", pcReport);
    }

    // Python console
    if (hiddenDockWindows.find("Std_PythonView") == std::string::npos) {
        PythonConsole* pcPython = new PythonConsole(this);
        ParameterGrp::handle hGrp = App::GetApplication().GetUserParameter().
            GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("General");

        if (hGrp->GetBool("PythonWordWrap", true)) {
          pcPython->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        } else {
          pcPython->setWordWrapMode(QTextOption::NoWrap);
        }

        pcPython->setWindowIcon(Gui::BitmapFactory().iconFromTheme("applications-python"));
        pcPython->setObjectName
            (QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","Python console")));
        pDockMgr->registerDockWindow("Std_PythonView", pcPython);
    }

    //Dag View.
    if (hiddenDockWindows.find("Std_DAGView") == std::string::npos) {
        //work through parameter.
        // old group name
        ParameterGrp::handle deprecateGroup = App::GetApplication().GetUserParameter().
              GetGroup("BaseApp")->GetGroup("Preferences");
        bool enabled = false;
        if (deprecateGroup->HasGroup("DAGView")) {
            deprecateGroup = deprecateGroup->GetGroup("DAGView");
            enabled = deprecateGroup->GetBool("Enabled", enabled);
        }
        // new group name
        ParameterGrp::handle group = App::GetApplication().GetUserParameter().
              GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("DockWindows")->GetGroup("DAGView");
        enabled = group->GetBool("Enabled", enabled);
        group->SetBool("Enabled", enabled); //ensure entry exists.
        if (enabled) {
            DAG::DockWindow *dagDockWindow = new DAG::DockWindow(nullptr, this);
            dagDockWindow->setObjectName
                (QString::fromLatin1(QT_TRANSLATE_NOOP("QDockWidget","DAG View")));
            pDockMgr->registerDockWindow("Std_DAGView", dagDockWindow);
        }
    }

    // accept drops on the window, get handled in dropEvent, dragEnterEvent
    setAcceptDrops(true);
    statusBar()->showMessage(tr("Ready"), 2001);
}

MainWindow::~MainWindow()
{
    delete d->status;
    delete d;
    instance = 0;
}

MainWindow* MainWindow::getInstance()
{
    // MainWindow has a public constructor
    return instance;
}

QMenu* MainWindow::createPopupMenu ()
{
    QMenu* menu = QMainWindow::createPopupMenu();
    Workbench* wb = WorkbenchManager::instance()->active();
    if (wb) {
        MenuItem item;
        wb->createMainWindowPopupMenu(&item);
        if (item.hasItems()) {
            menu->addSeparator();
            QList<MenuItem*> items = item.getItems();
            for (QList<MenuItem*>::iterator it = items.begin(); it != items.end(); ++it) {
                if ((*it)->command() == "Separator") {
                    menu->addSeparator();
                }
                else {
                    Command* cmd = Application::Instance->commandManager().getCommandByName((*it)->command().c_str());
                    if (cmd) cmd->addTo(menu);
                }
            }
        }
    }

    return menu;
}

void MainWindow::arrangeIcons()
{
    d->mdiArea->tileSubWindows();
}

void MainWindow::tile()
{
    d->mdiArea->tileSubWindows();
}

void MainWindow::cascade()
{
    d->mdiArea->cascadeSubWindows();
}

void MainWindow::closeActiveWindow ()
{
    d->mdiArea->closeActiveSubWindow();
}

void MainWindow::closeAllWindows ()
{
    d->mdiArea->closeAllSubWindows();
}

void MainWindow::activateNextWindow ()
{
    d->mdiArea->activateNextSubWindow();
}

void MainWindow::activatePreviousWindow ()
{
    d->mdiArea->activatePreviousSubWindow();
}

void MainWindow::activateWorkbench(const QString& name)
{
    // emit this signal
    workbenchActivated(name);
}

void MainWindow::showDocumentation(const QString& /*help*/)
{
}

bool MainWindow::event(QEvent *e)
{
    if (e->type() == QEvent::ApplicationWindowIconChange) {
        // if application icon changes apply it to the main window and the "About..." dialog
        this->setWindowIcon(QApplication::windowIcon());
        Command* about = Application::Instance->commandManager().getCommandByName("Std_About");
        if (about) {
            Action* action = about->getAction();
            if (action) action->setIcon(QApplication::windowIcon());
        }
    }
    return QMainWindow::event(e);
}

bool MainWindow::eventFilter(QObject* o, QEvent* e)
{
    if (o != this) {
        if (e->type() == QEvent::WindowStateChange) {
            // notify all mdi views when the active view receives a show normal, show minimized 
            // or show maximized event 
            MDIView * view = qobject_cast<MDIView*>(o);
            if (view) { // emit this signal
                Qt::WindowStates oldstate = static_cast<QWindowStateChangeEvent*>(e)->oldState();
                Qt::WindowStates newstate = view->windowState();
                if (oldstate != newstate)
                    windowStateChanged(view);
            }
        }

    }

    return QMainWindow::eventFilter(o, e);
}

void MainWindow::addWindow(MDIView* view)
{
    // make workspace parent of view
    bool isempty = d->mdiArea->subWindowList().isEmpty();
    QMdiSubWindow* child = new QMdiSubWindow(d->mdiArea->viewport());
    child->setAttribute(Qt::WA_DeleteOnClose);
    child->setWidget(view);
    child->setWindowIcon(view->windowIcon());
    QMenu* menu = child->systemMenu();

    // See StdCmdCloseActiveWindow (#0002631)
    QList<QAction*> acts = menu->actions();
    for (QList<QAction*>::iterator it = acts.begin(); it != acts.end(); ++it) {
        if ((*it)->shortcut() == QKeySequence(QKeySequence::Close)) {
            (*it)->setShortcuts(QList<QKeySequence>());
            break;
        }
    }

    QAction* action = menu->addAction(tr("Close All"));
    connect(action, SIGNAL(triggered()), d->mdiArea, SLOT(closeAllSubWindows()));
    d->mdiArea->addSubWindow(child);

    connect(view, SIGNAL(message(const QString&, int)),
            this, SLOT(showMessage(const QString&, int)));
    connect(this, SIGNAL(windowStateChanged(MDIView*)),
            view, SLOT(windowStateChanged(MDIView*)));

    // listen to the incoming events of the view
    view->installEventFilter(this);

    // show the very first window in maximized mode
    if (isempty)
        view->showMaximized();
    else
        view->show();
}

/**
 * Removes the instance of Gui::MDiView from the main window and sends am event
 * to the parent widget, a QMdiSubWindow to delete itself.
 * If you want to avoid that the Gui::MDIView instance gets destructed too you
 * must reparent it afterwards, e.g. set parent to NULL.
 */
void MainWindow::removeWindow(Gui::MDIView* view)
{
    // free all connections
    disconnect(view, SIGNAL(message(const QString&, int)),
               this, SLOT(showMessage(const QString&, int )));
    disconnect(this, SIGNAL(windowStateChanged(MDIView*)),
               view, SLOT(windowStateChanged(MDIView*)));
    view->removeEventFilter(this);

    // check if the focus widget is a child of the view
    QWidget* foc = this->focusWidget();
    if (foc) {
        QWidget* par = foc->parentWidget();
        while (par) {
            if (par == view) {
                foc->clearFocus();
                break;
            }
            par = par->parentWidget();
        }
    }

    QWidget* parent = view->parentWidget();
    // The call of 'd->mdiArea->removeSubWindow(parent)' causes the QMdiSubWindow
    // to lose its parent and thus the notification in QMdiSubWindow::closeEvent
    // of other mdi windows to get maximized if this window is maximized will fail.
    // However, we must let it here otherwise deleting MDI child views directly can
    // cause other problems.
    d->mdiArea->removeSubWindow(parent);
    parent->deleteLater();
}

void MainWindow::tabChanged(MDIView* view)
{
    Q_UNUSED(view);
}

void MainWindow::tabCloseRequested(int index)
{
    QTabBar* tab = d->mdiArea->findChild<QTabBar*>();
    if (index < 0 || index >= tab->count())
        return;

    const QList<QMdiSubWindow *> subWindows = d->mdiArea->subWindowList();
    Q_ASSERT(index < subWindows.size());

    QMdiSubWindow *subWindow = d->mdiArea->subWindowList().at(index);
    Q_ASSERT(subWindow);
    subWindow->close();
}

void MainWindow::onSetActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    d->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::setActiveWindow(MDIView* view)
{
    onSetActiveSubWindow(view->parentWidget());
    d->activeView = view;
    Application::Instance->viewActivated(view);
}

void MainWindow::onWindowActivated(QMdiSubWindow* w)
{
    if (!w) return;
    MDIView* view = dynamic_cast<MDIView*>(w->widget());

    // Even if windowActivated() signal is emitted mdi doesn't need to be a top-level window.
    // This happens e.g. if two windows are top-level and one of them gets docked again.
    // QWorkspace emits the signal then even though the other window is in front.
    // The consequence is that the docked window becomes the active window and not the undocked
    // window on top. This means that all accel events, menu and toolbar actions get redirected
    // to the (wrong) docked window.
    // But just testing whether the view is active and ignore it if not leads to other more serious problems -
    // at least under Linux. It seems to be a problem with the window manager.
    // Under Windows it seems to work though it's not really sure that it works reliably.
    // Result: So, we accept the first problem to be sure to avoid the second one.
    if ( !view /*|| !mdi->isActiveWindow()*/ ) 
        return; // either no MDIView or no valid object or no top-level window

    // set active the appropriate window (it needs not to be part of mdiIds, e.g. directly after creation)
    d->activeView = view;
    Application::Instance->viewActivated(view);
}

void MainWindow::onWindowsMenuAboutToShow()
{
    QList<QMdiSubWindow*> windows = d->mdiArea->subWindowList(QMdiArea::CreationOrder);
    QWidget* active = d->mdiArea->activeSubWindow();

    // We search for the 'Std_WindowsMenu' command that provides the list of actions
    CommandManager& cMgr = Application::Instance->commandManager();
    Command* cmd = cMgr.getCommandByName("Std_WindowsMenu");
    QList<QAction*> actions = qobject_cast<ActionGroup*>(cmd->getAction())->actions();

    // do the connection only once
    static bool firstShow = true;
    if (firstShow) {
        firstShow = false;
        QAction* last = actions.isEmpty() ? 0 : actions.last();
        for (QList<QAction*>::Iterator it = actions.begin(); it != actions.end(); ++it) {
            if (*it == last)
                break; // this is a separator
            connect(*it, SIGNAL(triggered()), d->windowMapper, SLOT(map()));
        }
    }

    int numWindows = std::min<int>(actions.count()-1, windows.count());
    for (int index = 0; index < numWindows; index++) {
        QWidget* child = windows.at(index);
        QAction* action = actions.at(index);
        QString text;
        QString title = child->windowTitle();
        int lastIndex = title.lastIndexOf(QString::fromLatin1("[*]"));
        if (lastIndex > 0) {
            title = title.left(lastIndex);
            if (child->isWindowModified())
                title = QString::fromLatin1("%1*").arg(title);
        }
        if (index < 9)
            text = QString::fromLatin1("&%1 %2").arg(index+1).arg(title);
        else
            text = QString::fromLatin1("%1 %2").arg(index+1).arg(title);
        action->setText(text);
        action->setVisible(true);
        action->setChecked(child == active);
        d->windowMapper->setMapping(action, child);
    }

    // if less windows than actions
    for (int index = numWindows; index < actions.count(); index++)
        actions[index]->setVisible(false);
    // show the separator
    if (numWindows > 0)
        actions.last()->setVisible(true);
}

void MainWindow::onToolBarMenuAboutToShow()
{
    QMenu* menu = static_cast<QMenu*>(sender());
    menu->clear();
    QList<QToolBar*> dock = this->findChildren<QToolBar*>();
    for (QList<QToolBar*>::Iterator it = dock.begin(); it != dock.end(); ++it) {
        if ((*it)->parentWidget() == this) {
            QAction* action = (*it)->toggleViewAction();
            action->setToolTip(tr("Toggles this toolbar"));
            action->setStatusTip(tr("Toggles this toolbar"));
//#            action->setWhatsThis(tr("Toggles this toolbar"));
            menu->addAction(action);
        }
    }
}

void MainWindow::onDockWindowMenuAboutToShow()
{
    QMenu* menu = static_cast<QMenu*>(sender());
    menu->clear();
    QList<QDockWidget*> dock = this->findChildren<QDockWidget*>();
    for (QList<QDockWidget*>::Iterator it = dock.begin(); it != dock.end(); ++it) {
        QAction* action = (*it)->toggleViewAction();
        action->setToolTip(tr("Toggles this dockable window"));
        action->setStatusTip(tr("Toggles this dockable window"));
//#        action->setWhatsThis(tr("Toggles this dockable window"));
        menu->addAction(action);
    }
}

QList<QWidget*> MainWindow::windows(QMdiArea::WindowOrder order) const
{
    QList<QWidget*> mdis;
    QList<QMdiSubWindow*> wnds = d->mdiArea->subWindowList(order);
    for (QList<QMdiSubWindow*>::iterator it = wnds.begin(); it != wnds.end(); ++it) {
        mdis << (*it)->widget();
    }
    return mdis;
}

// set text to the pane
void MainWindow::setPaneText(int i, QString text)
{
    if (i==1) {
        d->actionLabel->setText(text);
        d->actionTimer->setSingleShot(true);
        d->actionTimer->start(5000);
    }
    else if (i==2) {
        d->sizeLabel->setText(text);
    }
}

MDIView* MainWindow::activeWindow(void) const
{
    // each activated window notifies this main window when it is activated
    return d->activeView;
}

void MainWindow::closeEvent (QCloseEvent * e)
{
    Application::Instance->tryClose(e);
    if (e->isAccepted()) {
        // Send close event to all non-modal dialogs
        QList<QDialog*> dialogs = this->findChildren<QDialog*>();
        // It is possible that closing a dialog internally closes further dialogs. Thus,
        // we have to check the pointer before.
        QList< QPointer<QDialog> > dialogs_ptr;
        for (QList<QDialog*>::iterator it = dialogs.begin(); it != dialogs.end(); ++it) {
            dialogs_ptr.append(*it);
        }
        for (QList< QPointer<QDialog> >::iterator it = dialogs_ptr.begin(); it != dialogs_ptr.end(); ++it) {
            if (!(*it).isNull())
                (*it)->close();
        }
        QList<MDIView*> mdis = this->findChildren<MDIView*>();
        // Force to close any remaining (passive) MDI child views
        for (QList<MDIView*>::iterator it = mdis.begin(); it != mdis.end(); ++it) {
            (*it)->hide();
            (*it)->deleteLater();
        }
        d->activityTimer->stop();
        saveWindowSettings();
//        delete d->assistant;
//        d->assistant = 0;

        // See createMimeDataFromSelection
        QVariant prop = this->property("x-documentobject-file");
        if (!prop.isNull()) {
            Base::FileInfo fi((const char*)prop.toByteArray());
            if (fi.exists())
                fi.deleteFile();
        }

        /*emit*/ mainWindowClosed();
        if (this->property("QuitOnClosed").isValid()) {
            QApplication::closeAllWindows();
            qApp->quit(); // stop the event loop
        }
    }
}

void MainWindow::showEvent(QShowEvent  * /*e*/)
{
    // needed for logging
    std::clog << "Show main window" << std::endl;
    d->visibleTimer->start(15000);
}

void MainWindow::hideEvent(QHideEvent  * /*e*/)
{
    // needed for logging
    std::clog << "Hide main window" << std::endl;
    d->visibleTimer->stop();
}

void MainWindow::processMessages(const QList<QByteArray> & msg)
{
    // handle all the messages to open files
    try {
        WaitCursor wc;
        std::list<std::string> files;
        QByteArray action("OpenFile:");
        for (QList<QByteArray>::const_iterator it = msg.begin(); it != msg.end(); ++it) {
            if (it->startsWith(action))
                files.push_back(std::string(it->mid(action.size()).constData()));
        }
        files = App::Application::processFiles(files);
        for (std::list<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
            QString filename = QString::fromUtf8(it->c_str(), it->size());
            FileDialog::setWorkingDirectory(filename);
        }
    }
    catch (const Base::SystemExitException&) {
    }
}

void MainWindow::delayedStartup()
{
    // automatically run unit tests in Gui
    if (App::Application::Config()["RunMode"] == "Internal") {
        try {
            Base::Interpreter().runString(Base::ScriptFactory().ProduceScript("FreeCADTest"));
        }
        catch (const Base::SystemExitException&) {
            throw;
        }
        catch (const Base::Exception& e) {
            e.ReportException();
        }
        return;
    }

    // processing all command line files
    try {
        std::list<std::string> files = App::Application::getCmdLineFiles();
        files = App::Application::processFiles(files);
        for (std::list<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
            QString filename = QString::fromUtf8(it->c_str(), it->size());
            FileDialog::setWorkingDirectory(filename);
        }
    }
    catch (const Base::SystemExitException&) {
        throw;
    }

    const std::map<std::string,std::string>& cfg = App::Application::Config();
    std::map<std::string,std::string>::const_iterator it = cfg.find("StartHidden");
    if (it != cfg.end()) {
        QApplication::quit();
        return;
    }

    // Create new document?
    ParameterGrp::handle hGrp = WindowParameter::getDefaultParameter()->GetGroup("Document");
    if (hGrp->GetBool("CreateNewDoc", false)) {
        if (App::GetApplication().getDocuments().size()==0){
            App::GetApplication().newDocument();
        }
    }

    if (hGrp->GetBool("RecoveryEnabled", true)) {
        Application::Instance->checkForPreviousCrashes();
    }
}

void MainWindow::appendRecentFile(const QString& filename)
{
    RecentFilesAction *recent = this->findChild<RecentFilesAction *>
        (QString::fromLatin1("recentFiles"));
    if (recent) {
        recent->appendFile(filename);
    }
}

void MainWindow::updateActions()
{
    if (isVisible()) {
        Application::Instance->commandManager().testActive();
    }
}

void MainWindow::switchToTopLevelMode()
{
    QList<QDockWidget*> dw = this->findChildren<QDockWidget*>();
    for (QList<QDockWidget*>::Iterator it = dw.begin(); it != dw.end(); ++it) {
        (*it)->setParent(0, Qt::Window);
        (*it)->show();
    }
    QList<QWidget*> mdi = getMainWindow()->windows();
    for (QList<QWidget*>::Iterator it = mdi.begin(); it != mdi.end(); ++it) {
        (*it)->setParent(0, Qt::Window);
        (*it)->show();
    }
}

void MainWindow::switchToDockedMode()
{
    // Search for all top-level MDI views
    QWidgetList toplevel = QApplication::topLevelWidgets();
    for (QWidgetList::Iterator it = toplevel.begin(); it != toplevel.end(); ++it) {
        Gui::MDIView* view = qobject_cast<MDIView*>(*it);
        if (view)
            view->setCurrentViewMode(MDIView::Child);
    }
}

void MainWindow::loadWindowSettings()
{
    QString vendor = QString::fromLatin1(App::Application::Config()["ExeVendor"].c_str());
    QString application = QString::fromLatin1(App::Application::Config()["ExeName"].c_str());
//    int major = (QT_VERSION >> 0x10) & 0xff;
//    int minor = (QT_VERSION >> 0x08) & 0xff;
//    QString qtver = QString::fromLatin1("Qt%1.%2").arg(major).arg(minor);
    QSettings config(vendor, application);

    QRect rect = QApplication::desktop()->availableGeometry();
    int maxHeight = rect.height();
    int maxWidth = rect.width();

//    config.beginGroup(qtver);
    QPoint pos = config.value(QString::fromLatin1("Position"), this->pos()).toPoint();
    maxWidth -= pos.x();
    maxHeight -= pos.y();
    this->resize(config.value(QString::fromLatin1("Size"), QSize(maxWidth, maxHeight)).toSize());

    int x1,x2,y1,y2;
    // make sure that the main window is not totally out of the visible rectangle
    rect.getCoords(&x1, &y1, &x2, &y2);
    pos.setX(qMin(qMax(pos.x(),x1-this->width()+30),x2-30));
    pos.setY(qMin(qMax(pos.y(),y1-10),y2-10));
    this->move(pos);

    // tmp. disable the report window to suppress some bothering warnings
    Base::Console().SetEnabledMsgType("ReportOutput", ConsoleMsgType::MsgType_Wrn, false);
    this->restoreState(config.value(QString::fromLatin1("MainWindowState")).toByteArray());
    std::clog << "Main window restored" << std::endl;
    Base::Console().SetEnabledMsgType("ReportOutput", ConsoleMsgType::MsgType_Wrn, true);

    bool max = config.value(QString::fromLatin1("Maximized"), false).toBool();
    max ? showMaximized() : show();

    statusBar()->setVisible(config.value(QString::fromLatin1("StatusBar"), true).toBool());
//    config.endGroup();

    ToolBarManager::getInstance()->restoreState();
    std::clog << "Toolbars restored" << std::endl;
}

void MainWindow::saveWindowSettings()
{
    QString vendor = QString::fromLatin1(App::Application::Config()["ExeVendor"].c_str());
    QString application = QString::fromLatin1(App::Application::Config()["ExeName"].c_str());
//    int major = (QT_VERSION >> 0x10) & 0xff;
//    int minor = (QT_VERSION >> 0x08) & 0xff;
//    QString qtver = QString::fromLatin1("Qt%1.%2").arg(major).arg(minor);
    QSettings config(vendor, application);

//    config.beginGroup(qtver);
    config.setValue(QString::fromLatin1("Size"), this->size());
    config.setValue(QString::fromLatin1("Position"), this->pos());
    config.setValue(QString::fromLatin1("Maximized"), this->isMaximized());
    config.setValue(QString::fromLatin1("MainWindowState"), this->saveState());
    config.setValue(QString::fromLatin1("StatusBar"), this->statusBar()->isVisible());
//    config.endGroup();

    DockWindowManager::instance()->saveState();
    ToolBarManager::getInstance()->saveState();
}

/**
 * Drops the event \a e and tries to open the files.
 */
void MainWindow::dropEvent (QDropEvent* e)
{
	QMainWindow::dropEvent(e);
}

void MainWindow::dragEnterEvent (QDragEnterEvent * e)
{
	e->ignore();
}

QMimeData * MainWindow::createMimeDataFromSelection () const
{
    std::vector<SelectionSingleton::SelObj> selobj = Selection().getCompleteSelection();
    std::set<App::DocumentObject*> unique_objs;
    std::map< App::Document*, std::vector<App::DocumentObject*> > objs;
    for (std::vector<SelectionSingleton::SelObj>::iterator it = selobj.begin(); it != selobj.end(); ++it) {
        if (it->pObject && it->pObject->getDocument()) {
            if (unique_objs.insert(it->pObject).second)
                objs[it->pObject->getDocument()].push_back(it->pObject);
        }
    }

    if (objs.empty())
        return 0;

    std::vector<App::DocumentObject*> sel; // selected
    std::vector<App::DocumentObject*> all; // object sub-graph
    for (std::map< App::Document*, std::vector<App::DocumentObject*> >::iterator it = objs.begin(); it != objs.end(); ++it) {
        std::vector<App::DocumentObject*> dep = it->first->getDependencyList(it->second);
        sel.insert(sel.end(), it->second.begin(), it->second.end());
        all.insert(all.end(), dep.begin(), dep.end());
    }

    if (all.size() > sel.size()) {
        //check if selection are only geofeaturegroup objects, for them it is intuitive and wanted to copy the 
        //dependencies
        bool hasGroup = false, hasNormal = false;
        for(auto obj : sel) {
            if(obj->hasExtension(App::GroupExtension::getExtensionClassTypeId()))
                hasGroup = true;
            else 
                hasNormal = true;
        }
        if(hasGroup && !hasNormal) {
            sel = all;
        }
        else {
            //if there are normal objects selected it may be possible that some dependencies are 
            //from them, and not only from groups. so ask the user what to do.
            int ret = QMessageBox::question(getMainWindow(),
                tr("Object dependencies"),
                tr("The selected objects have a dependency to unselected objects.\n"
                "Do you want to copy them, too?"),
                QMessageBox::Yes,QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                sel = all;
            }
        }
    }

    unsigned int memsize=1000; // ~ for the meta-information
    for (std::vector<App::DocumentObject*>::iterator it = sel.begin(); it != sel.end(); ++it)
        memsize += (*it)->getMemSize();

    // if less than ~10 MB
    bool use_buffer=(memsize < 0xA00000);
    QByteArray res;
    try {
        res.reserve(memsize);
    }
    catch (const Base::MemoryException&) {
        use_buffer = false;
    }

    WaitCursor wc;
    QString mime;
    if (use_buffer) {
        mime = QLatin1String("application/x-documentobject");
        Base::ByteArrayOStreambuf buf(res);
        std::ostream str(&buf);
        // need this instance to call MergeDocuments::Save()
        App::Document* doc = sel.front()->getDocument();
        MergeDocuments mimeView(doc);
        doc->exportObjects(sel, str);
    }
    else {
        mime = QLatin1String("application/x-documentobject-file");
        static Base::FileInfo fi(App::Application::getTempFileName());
        Base::ofstream str(fi, std::ios::out | std::ios::binary);
        // need this instance to call MergeDocuments::Save()
        App::Document* doc = sel.front()->getDocument();
        MergeDocuments mimeView(doc);
        doc->exportObjects(sel, str);
        str.close();
        res = fi.filePath().c_str();

        // store the path name as a custom property and
        // delete this file when closing the application
        const_cast<MainWindow*>(this)->setProperty("x-documentobject-file", res);
    }

    QMimeData *mimeData = new QMimeData();
    mimeData->setData(mime,res);
    return mimeData;
}

bool MainWindow::canInsertFromMimeData (const QMimeData * source) const
{
    if (!source)
        return false;
    return
        source->hasFormat(QLatin1String("application/x-documentobject")) ||
        source->hasFormat(QLatin1String("application/x-documentobject-file"));
}

void MainWindow::insertFromMimeData (const QMimeData * mimeData)
{
    if (!mimeData)
        return;
    if (mimeData->hasFormat(QLatin1String("application/x-documentobject"))) {
        QByteArray res = mimeData->data(QLatin1String("application/x-documentobject"));
        App::Document* doc = App::GetApplication().getActiveDocument();
        if (!doc) doc = App::GetApplication().newDocument();

        doc->openTransaction("Paste");
        Base::ByteArrayIStreambuf buf(res);
        std::istream in(0);
        in.rdbuf(&buf);
        MergeDocuments mimeView(doc);
        std::vector<App::DocumentObject*> newObj = mimeView.importObjects(in);
        std::vector<App::DocumentObjectGroup*> grp = Gui::Selection().getObjectsOfType<App::DocumentObjectGroup>();
        if (grp.size() == 1) {
            Gui::Document* gui = Application::Instance->getDocument(doc);
            if (gui)
                gui->addRootObjectsToGroup(newObj, grp.front());
        }
        doc->commitTransaction();
    }
    else if (mimeData->hasFormat(QLatin1String("application/x-documentobject-file"))) {
        QByteArray res = mimeData->data(QLatin1String("application/x-documentobject-file"));
        App::Document* doc = App::GetApplication().getActiveDocument();
        if (!doc) doc = App::GetApplication().newDocument();

        doc->openTransaction("Paste");
        Base::FileInfo fi((const char*)res);
        Base::ifstream str(fi, std::ios::in | std::ios::binary);
        MergeDocuments mimeView(doc);
        std::vector<App::DocumentObject*> newObj = mimeView.importObjects(str);
        str.close();
        std::vector<App::DocumentObjectGroup*> grp = Gui::Selection().getObjectsOfType<App::DocumentObjectGroup>();
        if (grp.size() == 1) {
            Gui::Document* gui = Application::Instance->getDocument(doc);
            if (gui)
                gui->addRootObjectsToGroup(newObj, grp.front());
        }
        doc->commitTransaction();
    }
}

void MainWindow::setUrlHandler(const QString & /*scheme*/, Gui::UrlHandler* /*handler*/)
{
}

void MainWindow::unsetUrlHandler(const QString & /*scheme*/)
{
}

void MainWindow::loadUrls(App::Document* /*doc*/, const QList<QUrl>& /*url*/)
{
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        d->sizeLabel->setText(tr("Dimension"));
    
        CommandManager& rclMan = Application::Instance->commandManager();
        std::vector<Command*> cmd = rclMan.getAllCommands();
        for (std::vector<Command*>::iterator it = cmd.begin(); it != cmd.end(); ++it)
            (*it)->languageChange();

        // reload current workbench to retranslate all actions and window titles
        Workbench* wb = WorkbenchManager::instance()->active();
        if (wb) wb->retranslate();
    }
    else if (e->type() == QEvent::ActivationChange) {
        if (isActiveWindow()) {
            QMdiSubWindow* mdi = d->mdiArea->currentSubWindow();
            if (mdi) {
                MDIView* view = dynamic_cast<MDIView*>(mdi->widget());
                if (view && getMainWindow()->activeWindow() != view) {
                    d->activeView = view;
                    Application::Instance->viewActivated(view);
                }
            }
        }
    }
    else {
        QMainWindow::changeEvent(e);
    }
}

void MainWindow::showMessage (const QString& message, int timeout)
{
    QFontMetrics fm(statusBar()->font());
    QString msg = fm.elidedText(message, Qt::ElideMiddle, this->d->actionLabel->width());

    //#0000665: There is a crash under Ubuntu 12.04 (Qt 4.8.1)
    QMetaObject::invokeMethod(statusBar(), "showMessage",
        Qt::QueuedConnection,
        QGenericReturnArgument(),
        Q_ARG(QString,msg),
        Q_ARG(int, timeout));
}

// -------------------------------------------------------------

namespace Gui {

/**
 * The CustomMessageEvent class is used to send messages as events in the methods  
 * Error(), Warning() and Message() of the StatusBarObserver class to the main window 
 * to display them on the status bar instead of printing them directly to the status bar.
 *
 * This makes the usage of StatusBarObserver thread-safe.
 * @author Werner Mayer
 */
class CustomMessageEvent : public QEvent
{
public:
    enum Type {Msg, Wrn, Err, Log};
    CustomMessageEvent(Type t, const QString& s)
      : QEvent(QEvent::User), _type(t), msg(s)
    { }
    ~CustomMessageEvent()
    { }
    Type type() const
    { return _type; }
    const QString& message() const
    { return msg; }
private:
    Type _type;
    QString msg;
};
}

void MainWindow::customEvent(QEvent* e)
{
    if (e->type() == QEvent::User) {
        Gui::CustomMessageEvent* ce = static_cast<Gui::CustomMessageEvent*>(e);
        QString msg = ce->message();
        if (ce->type() == CustomMessageEvent::Log) {
            if (msg.startsWith(QLatin1String("#Inventor V2.1 ascii "))) {
                Gui::Document *d = Application::Instance->activeDocument();
                if (d) {
                    ViewProviderExtern *view = new ViewProviderExtern();
                    try {
                        view->setModeByString("1",msg.toLatin1().constData());
                        d->setAnnotationViewProvider("Vdbg",view);
                    }
                    catch (...) {
                        delete view;
                    }
                }
            }
        }
        else {
            d->actionLabel->setText(msg);
            d->actionTimer->setSingleShot(true);
            d->actionTimer->start(5000);
        }
    }
    else if (e->type() == ActionStyleEvent::EventType) {
        QList<TaskView::TaskView*> tasks = findChildren<TaskView::TaskView*>();
        if (static_cast<ActionStyleEvent*>(e)->getType() == ActionStyleEvent::Clear) {
            for (QList<TaskView::TaskView*>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
                (*it)->clearActionStyle();
            }
        }
        else {
            for (QList<TaskView::TaskView*>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
                (*it)->restoreActionStyle();
            }
        }
    }
}

// ----------------------------------------------------------

StatusBarObserver::StatusBarObserver()
  : WindowParameter("OutputWindow")
{
    msg = QString::fromLatin1("#000000"); // black
    wrn = QString::fromLatin1("#ffaa00"); // orange
    err = QString::fromLatin1("#ff0000"); // red
    Base::Console().AttachObserver(this);
    getWindowParameter()->Attach(this);
    getWindowParameter()->NotifyAll();
}

StatusBarObserver::~StatusBarObserver()
{
    getWindowParameter()->Detach(this);
    Base::Console().DetachObserver(this);
}

void StatusBarObserver::OnChange(Base::Subject<const char*> &rCaller, const char * sReason)
{
    ParameterGrp& rclGrp = ((ParameterGrp&)rCaller);
    if (strcmp(sReason, "colorText") == 0) {
        unsigned long col = rclGrp.GetUnsigned( sReason );
        this->msg = QColor((col >> 24) & 0xff,(col >> 16) & 0xff,(col >> 8) & 0xff).name();
    }
    else if (strcmp(sReason, "colorWarning") == 0) {
        unsigned long col = rclGrp.GetUnsigned( sReason );
        this->wrn = QColor((col >> 24) & 0xff,(col >> 16) & 0xff,(col >> 8) & 0xff).name();
    }
    else if (strcmp(sReason, "colorError") == 0) {
        unsigned long col = rclGrp.GetUnsigned( sReason );
        this->err = QColor((col >> 24) & 0xff,(col >> 16) & 0xff,(col >> 8) & 0xff).name();
    }
}

/** Get called when a message is issued. 
 * The message is displayed on the ststus bar. 
 */
void StatusBarObserver::Message(const char * m)
{
    // Send the event to the main window to allow thread-safety. Qt will delete it when done.
    QString txt = QString::fromLatin1("<font color=\"%1\">%2</font>").arg(this->msg, QString::fromUtf8(m));
    CustomMessageEvent* ev = new CustomMessageEvent(CustomMessageEvent::Msg, txt);
    QApplication::postEvent(getMainWindow(), ev);
}

/** Get called when a warning is issued. 
 * The message is displayed on the ststus bar. 
 */
void StatusBarObserver::Warning(const char *m)
{
    // Send the event to the main window to allow thread-safety. Qt will delete it when done.
    QString txt = QString::fromLatin1("<font color=\"%1\">%2</font>").arg(this->wrn, QString::fromUtf8(m));
    CustomMessageEvent* ev = new CustomMessageEvent(CustomMessageEvent::Wrn, txt);
    QApplication::postEvent(getMainWindow(), ev);
}

/** Get called when an error is issued. 
 * The message is displayed on the ststus bar. 
 */
void StatusBarObserver::Error  (const char *m)
{
    // Send the event to the main window to allow thread-safety. Qt will delete it when done.
    QString txt = QString::fromLatin1("<font color=\"%1\">%2</font>").arg(this->err, QString::fromUtf8(m));
    CustomMessageEvent* ev = new CustomMessageEvent(CustomMessageEvent::Err, txt);
    QApplication::postEvent(getMainWindow(), ev);
}

/** Get called when a log message is issued. 
 * The message is used to create an Inventor node for debug purposes. 
 */
void StatusBarObserver::Log(const char *m)
{
    // Send the event to the main window to allow thread-safety. Qt will delete it when done.
    CustomMessageEvent* ev = new CustomMessageEvent(CustomMessageEvent::Log, QString::fromUtf8(m));
    QApplication::postEvent(getMainWindow(), ev);
}

// -------------------------------------------------------------

int ActionStyleEvent::EventType = -1;

ActionStyleEvent::ActionStyleEvent(Style type)
  : QEvent(QEvent::Type(EventType)), type(type)
{
}

ActionStyleEvent::Style ActionStyleEvent::getType() const
{
    return type;
}


#include "moc_MainWindow.cpp"
