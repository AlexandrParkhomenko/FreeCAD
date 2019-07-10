/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "WorkbenchFactory.h"
#include "Workbench.h"

using namespace Gui;

Gui::WorkbenchFactoryInst* Gui::WorkbenchFactoryInst::_pcSingleton = 0;

WorkbenchFactoryInst& WorkbenchFactoryInst::instance()
{
  if (_pcSingleton == 0L)
    _pcSingleton = new WorkbenchFactoryInst;
  return *_pcSingleton;
}

void WorkbenchFactoryInst::destruct ()
{
  if ( _pcSingleton != 0 )
    delete _pcSingleton;
  _pcSingleton = 0;
}

Workbench* WorkbenchFactoryInst::createWorkbench ( const char* sName ) const
{
  Workbench* obj = (Workbench*)Produce( sName );
  Workbench* w = dynamic_cast<Workbench*>(obj);
  if ( !w )
  {
    delete obj; // delete the unknown object as no workbench object
    return 0;
  }

  w->setName( sName );
  return w;
}

std::list<std::string> WorkbenchFactoryInst::workbenches() const
{
  std::list<std::string> wb;
  for (std::map<const std::string, Base::AbstractProducer*>::const_iterator
      it = _mpcProducers.begin(); it != _mpcProducers.end(); ++it)
      wb.push_back(it->first);
  return wb;
}
