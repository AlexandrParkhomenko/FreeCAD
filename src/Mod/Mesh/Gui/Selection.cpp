/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "Selection.h"
#include "ui_Selection.h"

using namespace MeshGui;


/* TRANSLATOR MeshGui::Selection */

Selection::Selection(QWidget* parent)
    : QWidget(parent), ui(new Ui_Selection())
{
    ui->setupUi(this);
    ui->addSelection->installEventFilter(this);
    ui->clearSelection->installEventFilter(this);

    meshSel.setCheckOnlyVisibleTriangles(ui->visibleTriangles->isChecked());
    meshSel.setCheckOnlyPointToUserTriangles(ui->screenTriangles->isChecked());
}

/*
 *  Destroys the object and frees any allocated resources
 */
Selection::~Selection()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
    meshSel.clearSelection();
}

void Selection::setObjects(const std::vector<Gui::SelectionObject>& o)
{
    meshSel.setObjects(o);
}

std::vector<App::DocumentObject*> Selection::getObjects() const
{
    return meshSel.getObjects();
}

bool Selection::eventFilter(QObject* o, QEvent* e)
{
    if (e->type() == QEvent::HoverEnter) {
        if (o == ui->addSelection) {
            ui->label->setText(tr("Use a brush tool to select the area"));
        }
        else if (o == ui->clearSelection) {
            ui->label->setText(tr("Clears completely the selected area"));
        }
    }
    else if (e->type() == QEvent::HoverLeave) {
        if (o == ui->addSelection) {
            ui->label->clear();
        }
        else if (o == ui->clearSelection) {
            ui->label->clear();
        }
    }

    return false;
}

void Selection::on_addSelection_clicked()
{
    meshSel.startSelection();
}

void Selection::on_clearSelection_clicked()
{
    meshSel.clearSelection();
}

void Selection::on_visibleTriangles_toggled(bool on)
{
    meshSel.setCheckOnlyVisibleTriangles(on);
}

void Selection::on_screenTriangles_toggled(bool on)
{
    meshSel.setCheckOnlyPointToUserTriangles(on);
}

#include "moc_Selection.cpp"
