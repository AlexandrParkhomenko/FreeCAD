/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson <blobfish[at]gmx.com>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef DAGFILTER_H
#define DAGFILTER_H

#include <QString>

#include "DAGModelGraph.h"

namespace Gui
{
  class ViewProviderDocumentObject;
  namespace DAG
  {
    class FilterBase
    {
    public:
      enum class Type
      {
        None = 0, //!< no type designation. shouldn't be used.
        Inclusion,
        Exclusion
      };
      FilterBase();
      //! @return is whether we have a match or not.
      virtual bool goFilter(const Vertex &vertexIn, const Graph &graphIn, const GraphLinkContainer &linkIn) const = 0;
      QString name;
      bool enabled;
      Type type;
    };
    
    /*! Hide all children of app::origin that are not
     * used by subsequent features
     */
    class FilterOrigin : public FilterBase
    {
    public:
      FilterOrigin();
      virtual bool goFilter(const Vertex &vertexIn, const Graph &graphIn, const GraphLinkContainer &linkIn) const override;
    };
    
    /*! Hide nodes of type*/
    class FilterTyped : public FilterBase
    {
    public:
      explicit FilterTyped(const std::string &typeIn);
      std::string type;
      virtual bool goFilter(const Vertex &vertexIn, const Graph &graphIn, const GraphLinkContainer &linkIn) const override;
    };
  }
}

#endif // DAGFILTER_H
