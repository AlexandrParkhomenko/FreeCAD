/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_WORKBENCHFACTORY_H
#define GUI_WORKBENCHFACTORY_H

#include "stdexport.h"
#include "Base/Factory.h"
#include <string>
#include <list>

namespace Gui {
class Workbench;

/** 
 * The workbench factory provides methods for the dynamic creation of
 * special workbenches for each module. To create these workbenches once
 * they must be registered through a subclass of WorkbenchProducer.
 * @note To create workbenches you should use the API of WorkbenchManager.
 * @author Werner Mayer
 */
class GuiExport WorkbenchFactoryInst : public Base::Factory
{
public:
  /// The one and only instance.
  static WorkbenchFactoryInst& instance();
  /// Destructs the sole instance.
  static void destruct ();

  /** Creates the workbench with \a name. If no such workbench is registered
   * 0 is returned. 
   */
  Workbench* createWorkbench ( const char* sName ) const;
  /** Returns a list of all registered workbench classes. */
  std::list<std::string> workbenches() const;

private:
  static WorkbenchFactoryInst* _pcSingleton;

  WorkbenchFactoryInst(){}
  ~WorkbenchFactoryInst(){}
};

inline GuiExport WorkbenchFactoryInst& WorkbenchFactory()
{
  return WorkbenchFactoryInst::instance();
}

// --------------------------------------------------------------------

/**
 * The WorkbenchProducer template class allos the registration and the creation of workbench 
 * classes.
 * @author Werner Mayer
 */
template <class CLASS>
class WorkbenchProducer: public Base::AbstractProducer
{
public:
  WorkbenchProducer ()
  {
  }

  virtual ~WorkbenchProducer (){}

  virtual void* Produce () const
  {
    return (void*)(new CLASS);
  }
};

} // namespace Gui 

#endif // GUI_WORKBENCHFACTORY_H 
