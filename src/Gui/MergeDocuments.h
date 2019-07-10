/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_MERGEDOCUMENTS_H
#define GUI_MERGEDOCUMENTS_H

#include "stdexport.h"
#include <boost/signals2.hpp>
#include "Base/Persistence.h"

namespace App {
class Document;
class DocumentObject;
}

namespace Gui {
class Document;
class GuiExport MergeDocuments : public Base::Persistence
{
public:
    MergeDocuments(App::Document* doc);
    ~MergeDocuments();
    unsigned int getMemSize (void) const;
    std::vector<App::DocumentObject*> importObjects(std::istream&);
    void importObject(const std::vector<App::DocumentObject*>& o, Base::XMLReader & r);
    void exportObject(const std::vector<App::DocumentObject*>& o, Base::Writer & w);
    void Save (Base::Writer & w) const;
    void Restore(Base::XMLReader &r);
    void SaveDocFile (Base::Writer & w) const;
    void RestoreDocFile(Base::Reader & r);

private:
    std::istream* stream;
    App::Document* appdoc;
    Gui::Document* document;
    std::vector<App::DocumentObject*> objects;
    std::map<std::string, std::string> nameMap;
    typedef boost::signals2::connection Connection;
    Connection connectExport;
    Connection connectImport;
};

} // namespace Gui

#endif // GUI_MERGEDOCUMENTS_H
