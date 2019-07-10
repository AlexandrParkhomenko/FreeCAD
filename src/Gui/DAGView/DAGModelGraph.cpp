/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson <blobfish[at]gmx.com>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "DAGModelGraph.h"

using namespace Gui;
using namespace DAG;

VertexProperty::VertexProperty() : 
  rectangle(new RectItem()),
  point(new QGraphicsEllipseItem()), 
  visibleIcon(new QGraphicsPixmapItem()),
  stateIcon(new QGraphicsPixmapItem()),
  icon(new QGraphicsPixmapItem()),
  text(new QGraphicsTextItem()),
  row(0),
  column(0),
  topoSortIndex(0),
  lastVisibleState(VisibilityState::None),
  lastFeatureState(FeatureState::None),
  dagVisible(true)
{
  //set z values.
  this->rectangle->setZValue(-1000.0);
  this->point->setZValue(1000.0);
  this->visibleIcon->setZValue(0.0);
  this->stateIcon->setZValue(0.0);
  this->icon->setZValue(0.0);
  this->text->setZValue(0.0);
}

EdgeProperty::EdgeProperty() : relation(BranchTag::None)
{

}

bool Gui::DAG::hasRecord(const App::DocumentObject* dObjectIn, const GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByDObject>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByDObject>();
  List::const_iterator it = list.find(dObjectIn);
  return it != list.end();
}

const GraphLinkRecord& Gui::DAG::findRecord(Vertex vertexIn, const GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByVertex>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByVertex>();
  List::const_iterator it = list.find(vertexIn);
  assert(it != list.end());
  return *it;
}

const GraphLinkRecord& Gui::DAG::findRecord(const App::DocumentObject* dObjectIn, const GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByDObject>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByDObject>();
  List::const_iterator it = list.find(dObjectIn);
  assert(it != list.end());
  return *it;
}

const GraphLinkRecord& Gui::DAG::findRecord(const ViewProviderDocumentObject* VPDObjectIn, const GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByVPDObject>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByVPDObject>();
  List::const_iterator it = list.find(VPDObjectIn);
  assert(it != list.end());
  return *it;
}

const GraphLinkRecord& Gui::DAG::findRecord(const RectItem* rectIn, const GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByRectItem>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByRectItem>();
  List::const_iterator it = list.find(rectIn);
  assert(it != list.end());
  return *it;
}

const GraphLinkRecord& Gui::DAG::findRecord(const std::string &stringIn, const GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByUniqueName>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByUniqueName>();
  List::const_iterator it = list.find(stringIn);
  assert(it != list.end());
  return *it;
}

void Gui::DAG::eraseRecord(const ViewProviderDocumentObject* VPDObjectIn, GraphLinkContainer &containerIn)
{
  typedef GraphLinkContainer::index<GraphLinkRecord::ByVPDObject>::type List;
  const List &list = containerIn.get<GraphLinkRecord::ByVPDObject>();
  List::iterator it = list.find(VPDObjectIn);
  assert(it != list.end());
  containerIn.get<GraphLinkRecord::ByVPDObject>().erase(it);
}
