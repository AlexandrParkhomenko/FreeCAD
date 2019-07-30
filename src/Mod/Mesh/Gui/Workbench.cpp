/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <qobject.h>
# include <QGroupBox>
# include <QLabel>

#include "Workbench.h"
#include "Gui/Application.h"
#include "Gui/Command.h"
#include "Gui/MenuManager.h"
#include "Gui/ToolBarManager.h"
#include "Gui/Selection.h"
#include "Gui/TaskView/TaskView.h"

#include "../App/MeshFeature.h"

using namespace MeshGui;

#if 0 // needed for Qt's lupdate utility
    qApp->translate("Workbench", "Analyze");
    qApp->translate("Workbench", "Boolean");
    qApp->translate("Workbench", "&Meshes");
    qApp->translate("Workbench", "Mesh tools");
#endif

/// @namespace MeshGui @class Workbench
TYPESYSTEM_SOURCE(MeshGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
}

Workbench::~Workbench()
{
}

class MeshInfoWatcher : public Gui::TaskView::TaskWatcher, public Gui::SelectionObserver
{
public:
    MeshInfoWatcher() : TaskWatcher(0)
    {
        labelPoints = new QLabel();
        labelPoints->setText(QString("Number of points:"));

        labelFacets = new QLabel();
        labelFacets->setText(QString("Number of facets:"));

        numPoints = new QLabel();
        numFacets = new QLabel();

        labelMin = new QLabel();
        labelMin->setText(QString("Minimum bound:"));

        labelMax = new QLabel();
        labelMax->setText(QString("Maximum bound:"));

        numMin = new QLabel();
        numMax = new QLabel();

        QGroupBox* box = new QGroupBox();
        box->setTitle(QString("Mesh info box"));
        //box->setAutoFillBackground(true);
        QGridLayout* grid = new QGridLayout(box);
        grid->addWidget(labelPoints, 0, 0);
        grid->addWidget(numPoints, 0, 1);
        grid->addWidget(labelFacets, 1, 0);
        grid->addWidget(numFacets, 1, 1);

        grid->addWidget(labelMin, 2, 0);
        grid->addWidget(numMin, 2, 1);
        grid->addWidget(labelMax, 3, 0);
        grid->addWidget(numMax, 3, 1);

        Gui::TaskView::TaskBox* taskbox = new Gui::TaskView::TaskBox(
            QPixmap(), QString("Mesh info"), false, 0);
        taskbox->groupLayout()->addWidget(box);
        Content.push_back(taskbox);
    }
    bool shouldShow(void)
    {
        return true;
    }
    void onSelectionChanged(const Gui::SelectionChanges&)
    {
        Base::BoundBox3d bbox;
        unsigned long countPoints=0, countFacets=0;
        std::vector<Mesh::Feature*> mesh = Gui::Selection().getObjectsOfType<Mesh::Feature>();
        for (std::vector<Mesh::Feature*>::iterator it = mesh.begin(); it != mesh.end(); ++it) {
            countPoints += (*it)->Mesh.getValue().countPoints();
            countFacets += (*it)->Mesh.getValue().countFacets();
            bbox.Add((*it)->Mesh.getBoundingBox());
        }

        if (countPoints > 0) {
            numPoints->setText(QString::number(countPoints));
            numFacets->setText(QString::number(countFacets));
            numMin->setText(QString("X: %1\tY: %2\tZ: %3")
                .arg(bbox.MinX).arg(bbox.MinX).arg(bbox.MinX));
            numMax->setText(QString("X: %1\tY: %2\tZ: %3")
                .arg(bbox.MaxX).arg(bbox.MaxX).arg(bbox.MaxX));
        }
        else {
            numPoints->setText(QString(""));
            numFacets->setText(QString(""));
            numMin->setText(QString(""));
            numMax->setText(QString(""));
        }
    }

private:
    QLabel* labelPoints;
    QLabel* numPoints;
    QLabel* labelFacets;
    QLabel* numFacets;
    QLabel* labelMin;
    QLabel* numMin;
    QLabel* labelMax;
    QLabel* numMax;
};

void Workbench::activated()
{
    Gui::Workbench::activated();

    std::vector<Gui::TaskView::TaskWatcher*> Watcher;
    Watcher.push_back(new MeshInfoWatcher);
    addTaskWatcher(Watcher);
}

void Workbench::deactivated()
{
    Gui::Workbench::deactivated();
    removeTaskWatcher();

}

void Workbench::setupContextMenu(const char* recipient,Gui::MenuItem* item) const
{
    StdWorkbench::setupContextMenu( recipient, item );
    if (Gui::Selection().countObjectsOfType(Mesh::Feature::getClassTypeId()) > 0)
    {
        *item << "Separator" << "Mesh_Import" << "Mesh_Export" << "Mesh_VertexCurvature";
    }
}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows");
    Gui::MenuItem* mesh = new Gui::MenuItem;
    root->insertItem( item, mesh );

    // analyze
    Gui::MenuItem* analyze = new Gui::MenuItem;
    analyze->setCommand("Analyze");
    *analyze << "Mesh_Evaluation" << "Mesh_EvaluateFacet" << "Mesh_CurvatureInfo" << "Separator" 
             << "Mesh_EvaluateSolid" << "Mesh_BoundingBox";

    // boolean
    Gui::MenuItem* boolean = new Gui::MenuItem;
    boolean->setCommand("Boolean");
    *boolean << "Mesh_Union"
             << "Mesh_Intersection"
             << "Mesh_Difference";

    // cutting
    Gui::MenuItem* cutting = new Gui::MenuItem;
    cutting->setCommand("Cutting");
    *cutting << "Mesh_PolyCut"
             << "Mesh_PolyTrim"
           //<< "Mesh_PolySegm"
             << "Mesh_TrimByPlane"
             << "Mesh_SectionByPlane";

    mesh->setCommand("&Meshes");
    *mesh << "Mesh_Import"
          << "Mesh_Export"
          << "Mesh_FromPartShape"
          << "Separator"
          << analyze
          << "Mesh_VertexCurvature"
          << "Mesh_HarmonizeNormals"
          << "Mesh_FlipNormals"
          << "Separator"
          << "Mesh_FillupHoles"
          << "Mesh_FillInteractiveHole"
          << "Mesh_AddFacet"
          << "Mesh_RemoveComponents"
          << "Mesh_RemoveCompByHand"
          << "Mesh_Segmentation"
          << "Mesh_SegmentationBestFit"
          << "Separator"
          << "Mesh_Smoothing"
          << "Mesh_Scale"
          << "Separator"
          << "Mesh_BuildRegularSolid"
          << boolean
          << cutting
          << "Separator"
          << "Mesh_Merge"
          << "Separator";
    Gui::CommandManager& mgr = Gui::Application::Instance->commandManager();
    if (mgr.getCommandByName("MeshPart_CreateFlatMesh"))
        *mesh << "MeshPart_CreateFlatMesh";
    if (mgr.getCommandByName("MeshPart_CreateFlatFace"))
        *mesh << "MeshPart_CreateFlatFace";
    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();
    Gui::ToolBarItem* mesh = new Gui::ToolBarItem(root);
    mesh->setCommand("Mesh tools");
    *mesh << "Mesh_Import" << "Mesh_Export" << "Separator" << "Mesh_PolyCut" << "Mesh_VertexCurvature";
    return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // Mesh tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    Gui::ToolBarItem* mesh;

    mesh = new Gui::ToolBarItem( root );
    mesh->setCommand("Mesh tools");
    *mesh << "Mesh_Import" << "Mesh_Export" << "Mesh_PolyCut";

    mesh = new Gui::ToolBarItem( root );
    mesh->setCommand("Mesh test suite");
    *mesh << "Mesh_Demolding" << "Mesh_Transform" << "Separator" ;

    return root;
}

