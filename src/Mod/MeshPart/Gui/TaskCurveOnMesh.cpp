/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "TaskCurveOnMesh.h"
#include "ui_TaskCurveOnMesh.h"
#include "CurveOnMesh.h"

#include "Gui/Application.h"
#include "Gui/Document.h"
#include "Gui/View3DInventor.h"
#include "Gui/View3DInventorViewer.h"


using namespace MeshPartGui;

CurveOnMeshWidget::CurveOnMeshWidget(Gui::View3DInventor* view, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui_TaskCurveOnMesh())
    , myCurveHandler(new CurveOnMeshHandler(this))
    , myView(view)
{
    ui->setupUi(this);
    this->setup();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CurveOnMeshWidget::~CurveOnMeshWidget()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

void CurveOnMeshWidget::setup()
{
    ui->meshTolerance->setValue(0.2);
    ui->continuity->addItem(QString::fromLatin1("C0"), static_cast<int>(GeomAbs_C0));
    ui->continuity->addItem(QString::fromLatin1("C1"), static_cast<int>(GeomAbs_C1));
    ui->continuity->addItem(QString::fromLatin1("C2"), static_cast<int>(GeomAbs_C2));
    ui->continuity->addItem(QString::fromLatin1("C3"), static_cast<int>(GeomAbs_C3));
    ui->continuity->setCurrentIndex(2);

    for (int i=0; i<8; i++)
        ui->maxDegree->addItem(QString::number(i+1));
    ui->maxDegree->setCurrentIndex(4);
}

void CurveOnMeshWidget::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

void CurveOnMeshWidget::on_startButton_clicked()
{
    int cont = ui->continuity->itemData(ui->continuity->currentIndex()).toInt();
    myCurveHandler->setParameters(ui->maxDegree->currentIndex(),
                                  static_cast<GeomAbs_Shape>(cont),
                                  ui->meshTolerance->value(),
                                  ui->splitAngle->value().getValue());
    myCurveHandler->enableCallback(myView);
}

void CurveOnMeshWidget::reject()
{
}

// ----------------------------------------------------------------------------

TaskCurveOnMesh::TaskCurveOnMesh(Gui::View3DInventor* view)
{
    widget = new CurveOnMeshWidget(view);
    taskbox = new Gui::TaskView::TaskBox(
        QPixmap(),
        widget->windowTitle(), true, 0);
    taskbox->groupLayout()->addWidget(widget);
    Content.push_back(taskbox);
}

TaskCurveOnMesh::~TaskCurveOnMesh()
{
    // automatically deleted in the sub-class
}

bool TaskCurveOnMesh::reject()
{
    widget->reject();
    return true;
}

#include "moc_TaskCurveOnMesh.cpp"
