/***************************************************************************
*   (c) Jürgen Riegel (juergen.riegel@web.de) 2014                        *
*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
*   Juergen Riegel 2014                                                   *
***************************************************************************/




#include "ActiveObjectList.h"
#include "Gui/Application.h"
#include "Gui/Document.h"
#include "Gui/ViewProviderDocumentObject.h"



using namespace Gui;


void Gui::ActiveObjectList::setObject(App::DocumentObject* obj, const char* name, const Gui::HighlightMode& mode)
{
    ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/TreeView");
    bool autoExpand = hGrp->GetBool("TreeActiveAutoExpand", true);

    if (hasObject(name)) {
        App::DocumentObject* act = getObject<App::DocumentObject*>(name);
        Gui::Document* doc = Application::Instance->getDocument(act->getDocument());
        Gui::ViewProviderDocumentObject* viewProvider = static_cast
                <Gui::ViewProviderDocumentObject*>(doc->getViewProvider(act));
        doc->signalHighlightObject(*viewProvider, mode, false);
        if (autoExpand)
            doc->signalExpandObject(*viewProvider, Gui::CollapseItem);
    }

    if (obj) {
        Gui::Document* doc = Application::Instance->getDocument(obj->getDocument());
        Gui::ViewProviderDocumentObject* viewProvider = static_cast
                <Gui::ViewProviderDocumentObject*>(doc->getViewProvider(obj));
        doc->signalHighlightObject(*viewProvider, mode, true);
        if (autoExpand)
            doc->signalExpandObject(*viewProvider, Gui::ExpandPath);
        _ObjectMap[name] = obj;
    }
    else {
        if (hasObject(name))
            _ObjectMap.erase(name);
    }
}

bool Gui::ActiveObjectList::hasObject(const char*name)const 
{
    return _ObjectMap.find(name) != _ObjectMap.end();
}

void ActiveObjectList::objectDeleted(const ViewProviderDocumentObject& viewProviderIn)
{
  App::DocumentObject* object = viewProviderIn.getObject();
  //maybe boost::bimap or boost::multi_index
  std::map<std::string, App::DocumentObject*>::iterator it;
  for (it = _ObjectMap.begin(); it != _ObjectMap.end(); ++it)
  {
    if (it->second == object)
    {
      _ObjectMap.erase(it);
      return;
    }
  }
}
