/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QEvent>
# include <QGridLayout>
# include <QSizePolicy>
# include <QPushButton>

#include "DlgCustomizeImp.h"
#include "MainWindow.h"
#include "WidgetFactory.h"

using namespace Gui::Dialog;

QList<QByteArray> DlgCustomizeImp::_pages;

/* TRANSLATOR Gui::Dialog::DlgCustomizeImp */

/**
 *  Constructs a DlgCustomizeImp which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgCustomizeImp::DlgCustomizeImp(QWidget* parent, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
    setModal(false);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    resize( 690, 365 ); 

    setWindowTitle(tr("Customize"));
    setSizeGripEnabled( true );

    customLayout = new QGridLayout( this ); 
    customLayout->setSpacing( 6 );
    customLayout->setMargin( 11 );

    layout = new QHBoxLayout; 
    layout->setSpacing( 6 );
    layout->setMargin( 0 );

    buttonHelp = new QPushButton( this );
    buttonHelp->setText(tr("&Help"));
    layout->addWidget( buttonHelp );

    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout->addItem(spacer);

    buttonClose = new QPushButton( this );
    buttonClose->setText(tr("&Close"));
    layout->addWidget(buttonClose);

    customLayout->addLayout( layout, 1, 0 );

    tabWidget = new QTabWidget( this );

    // make sure that pages are ready to create
    GetWidgetFactorySupplier();
    for (QList<QByteArray>::Iterator it = _pages.begin(); it!=_pages.end(); ++it)
    {
        addPage(WidgetFactory().createWidget((*it).constData()));
    }

    customLayout->addWidget(tabWidget, 0, 0);


    // tab order
    setTabOrder(tabWidget, buttonClose);
    setTabOrder(buttonClose, buttonHelp);

    // connections
    //
//#    connect(buttonHelp,  SIGNAL (clicked()), getMainWindow(), SLOT (whatsThis()));
    connect(buttonClose, SIGNAL (clicked()), this, SLOT (close()));
}

/**
 *  Destroys the object and frees any allocated resources
 */
DlgCustomizeImp::~DlgCustomizeImp()
{
    // no need to delete child widgets, Qt does it all for us
}

/**
 * Adds a customize page with its class name \a className.
 * To create this page it must be registered in the WidgetFactory.
 * @see WidgetFactory
 * @see CustomPageProducer
 */
void DlgCustomizeImp::addPage(const char* className)
{
    _pages.push_back(className);
}

/** Inserts a new tab page with its caption */
void DlgCustomizeImp::addPage (QWidget* w)
{
    tabWidget->addTab(w, w->windowTitle());
}

void DlgCustomizeImp::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        setWindowTitle(tr("Customize"));
        buttonHelp->setText(tr("&Help"));
        buttonClose->setText(tr("&Close"));
        int count = tabWidget->count();
        for (int i=0; i<count; i++) {
            QWidget* w = tabWidget->widget(i);
            tabWidget->setTabText(i, w->windowTitle());
        }
    }
    QDialog::changeEvent(e);
}

#include "moc_DlgCustomizeImp.cpp"
