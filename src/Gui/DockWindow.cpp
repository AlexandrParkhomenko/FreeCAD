/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "DockWindow.h"

using namespace Gui;

DockWindow::DockWindow( Gui::Document* pcDocument, QWidget *parent)
  : QWidget( parent ), BaseView( pcDocument )
{
}

DockWindow::~DockWindow()
{
}

#include "moc_DockWindow.cpp"
