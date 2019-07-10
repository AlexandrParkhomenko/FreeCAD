/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_MERGEDOCUMENTS_H
#define APP_MERGEDOCUMENTS_H

#include "stdexport.h"
#include <boost/signals2.hpp>
#include "Base/Persistence.h"

namespace App {
class Document;
class DocumentObject;
class AppExport MergeDocuments : public Base::Persistence
{
public:
    MergeDocuments(App::Document* doc);
    ~MergeDocuments();
    bool isVerbose() const { return verbose; }
    void setVerbose(bool on) { verbose = on; }
    unsigned int getMemSize (void) const;
    std::vector<App::DocumentObject*> importObjects(std::istream&);
    void importObject(const std::vector<App::DocumentObject*>& o, Base::XMLReader & r);
    void exportObject(const std::vector<App::DocumentObject*>& o, Base::Writer & w);
    void Save (Base::Writer & w) const;
    void Restore(Base::XMLReader &r);
    void SaveDocFile (Base::Writer & w) const;
    void RestoreDocFile(Base::Reader & r);

private:
    bool guiup;
    bool verbose;
    std::ifstream* stream;
    App::Document* appdoc;
    std::vector<App::DocumentObject*> objects;
    std::map<std::string, std::string> nameMap;
    typedef boost::signals2::connection Connection;
    Connection connectExport;
    Connection connectImport;
};

} // namespace App

#endif // APP_MERGEDOCUMENTS_H
