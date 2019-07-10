/***************************************************************************
*   (c) Jürgen Riegel (juergen.riegel@web.de) 2014                        *
*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
*   Juergen Riegel 2014                                                   *
***************************************************************************/


#ifndef GUI_ActiveObjectList_H
#define GUI_ActiveObjectList_H

#include "stdexport.h"
#include <map>
#include "Tree.h"
namespace App {
    class DocumentObject;
}

namespace Gui
{

    class Document;
    class ViewProviderDocumentObject;

   /** List of active or special objects
    * This class holds a list of objects with a special name.
    * Its mainly used to points to something like the active Body or Part in a edit session.
    * The class is used the viewer (editor) of a document.
    * @see Gui::MDIViewer
    * @author Jürgen Riegel
    */
    class GuiExport ActiveObjectList
    {

    public:
        template<typename _T>
        inline _T getObject(const char* name) const
        {
            std::map<std::string, App::DocumentObject*>::const_iterator pos = _ObjectMap.find(name);
            return  pos == _ObjectMap.end() ? 0 : dynamic_cast<_T>(pos->second);
        }
        void setObject(App::DocumentObject*, const char*, const Gui::HighlightMode& m = Gui::UserDefined);
        bool hasObject(const char*)const;
        void objectDeleted(const ViewProviderDocumentObject& viewProviderIn);
    protected:
        std::map<std::string, App::DocumentObject*> _ObjectMap;
    };

} //namespace Gui

static const char PDBODYKEY[] = "pdbody";
static const char PARTKEY[] = "part";

#endif 
