/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002                        *   
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/



#	include <list>


#include "Factory.h"
#include "Console.h"

using namespace Base;


Factory::~Factory ()
{
  for (std::map<const std::string, AbstractProducer*>::iterator pI = _mpcProducers.begin(); pI != _mpcProducers.end(); ++pI)
    delete pI->second;
}

void* Factory::Produce (const char *sClassName) const
{
  std::map<const std::string, AbstractProducer*>::const_iterator pProd;

  pProd = _mpcProducers.find(sClassName);
  if (pProd != _mpcProducers.end())
    return pProd->second->Produce();
  else
    return NULL;
}

void Factory::AddProducer (const char *sClassName, AbstractProducer *pcProducer)
{
  _mpcProducers[sClassName] = pcProducer;
}

bool Factory::CanProduce(const char* sClassName) const
{
  return (_mpcProducers.find(sClassName) != _mpcProducers.end());
}

std::list<std::string> Factory::CanProduce() const
{
  std::list<std::string> lObjects;

  for (std::map<const std::string, AbstractProducer*>::const_iterator pI = _mpcProducers.begin(); pI != _mpcProducers.end(); ++pI)
  {
    lObjects.push_back(pI->first);
  }

  return lObjects;
}

// ----------------------------------------------------

ScriptFactorySingleton* ScriptFactorySingleton::_pcSingleton = NULL;



ScriptFactorySingleton& ScriptFactorySingleton::Instance(void)
{
  if (_pcSingleton == NULL)
    _pcSingleton = new ScriptFactorySingleton;
  return *_pcSingleton;
}

void ScriptFactorySingleton::Destruct (void)
{
  if (_pcSingleton != 0)
    delete _pcSingleton;
  _pcSingleton = 0;
}

const char* ScriptFactorySingleton::ProduceScript (const char* sScriptName) const
{
  const char* script = (const char*)Produce(sScriptName);

  if ( !script )
  {
#ifdef FC_DEBUG
    Console().Warning("\"%s\" is not registered\n", sScriptName);
#endif
    return ""; // no data
  }

  return script;
}
