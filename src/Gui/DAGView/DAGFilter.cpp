/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson <blobfish[at]gmx.com>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "Base/Type.h"
#include "Gui/ViewProviderDocumentObject.h"


#include "DAGFilter.h"

using namespace Gui;
using namespace DAG;

FilterBase::FilterBase() : name(QString::fromLatin1("empty name")), enabled(true), type(Type::Exclusion)
{

}

FilterOrigin::FilterOrigin() : FilterBase()
{
  name = QObject::tr("Origin");
}

bool FilterOrigin::goFilter(const Vertex &vertexIn, const Graph &graphIn, const GraphLinkContainer &linkIn) const
{
  Base::Type originType = Base::Type::fromName("App::Origin");
  assert (originType != Base::Type::badType());
  //if child of origin hide.
  InEdgeIterator it, itEnd;
  for (boost::tie(it, itEnd) = boost::in_edges(vertexIn, graphIn); it != itEnd; ++it)
  {
    Vertex source = boost::source(*it, graphIn);
    const GraphLinkRecord &sourceRecord = findRecord(source, linkIn);
    if
    (
      (sourceRecord.DObject->getTypeId() == originType) &&
      (boost::in_degree(vertexIn, graphIn) == 1)
    )
      return true;
  }
  return false;
}

FilterTyped::FilterTyped(const std::string &typeIn) : FilterBase(), type(typeIn)
{
  name = QString::fromStdString(typeIn);
}

bool FilterTyped::goFilter(const Gui::DAG::Vertex& vertexIn, const Graph& graphIn, const GraphLinkContainer& linkIn) const
{
  Q_UNUSED(graphIn); 
  if (type.empty())
    return false;
  Base::Type theType = Base::Type::fromName(type.c_str());
  if (theType == Base::Type::badType())
    return false;
  
  const GraphLinkRecord &sourceRecord = findRecord(vertexIn, linkIn);
  if (sourceRecord.DObject->getTypeId() == theType)
    return true;
  
  return false;
}


