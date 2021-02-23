/***************************************************************************
 *   Copyright (c) 2012 Juergen Riegel <juergen.riegel@web.de>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <boost/bind/bind.hpp>
# include <QAction>
# include <QActionGroup>
# include <QApplication>
# include <qcursor.h>
# include <qlayout.h>
# include <qstatusbar.h>
# include <QContextMenuEvent>
# include <QMenu>
# include <QPixmap>
# include <QTimer>

#include <QDirModel>
#include "Base/Console.h"
#include "App/Document.h"

#include "ProjectView.h"
#include "Document.h"
#include "BitmapFactory.h"
#include "ViewProviderDocumentObject.h"
#include "MenuManager.h"
#include "Application.h"
#include "MainWindow.h"

using namespace Gui;



/* TRANSLATOR Gui::ProjectWidget */
ProjectWidget::ProjectWidget(QWidget* parent)
    : QTreeView(parent)
{
    fileModel = new QDirModel(this);
    fileModel->setSorting(QDir::DirsFirst | QDir::Type);
    setModel(fileModel);
}

ProjectWidget::~ProjectWidget()
{
}





#include "moc_ProjectView.cpp"

