/***************************************************************************
 *   Copyright (c) 2015 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_AUTOSAVER_H
#define GUI_AUTOSAVER_H

#include <QObject>
#include "Base/Writer.h"
#include <map>
#include <set>
#include <string>
#include <boost/signals2.hpp>

namespace App {
class Document;
class DocumentObject;
class Property;
}

namespace Gui {
class ViewProvider;

class AutoSaveProperty
{
public:
    AutoSaveProperty(const App::Document* doc);
    ~AutoSaveProperty();
    int timerId;
    std::set<std::string> touched;
    std::string dirName;
    std::map<std::string, std::string> fileMap;

private:
    void slotNewObject(const App::DocumentObject&);
    void slotChangePropertyData(const App::Property&);
    typedef boost::signals2::connection Connection;
    Connection documentNew;
    Connection documentMod;
};

/*!
 The class AutoSaver is used to automatically save a document to a temporary file.
 @author Werner Mayer
 */
class AutoSaver : public QObject
{
    Q_OBJECT

private:
    static AutoSaver* self;
    AutoSaver(QObject* parent);
    virtual ~AutoSaver();

public:
    static AutoSaver* instance();
    /*!
     Sets the timeout in milliseconds. A value of 0 means that no timer is used.
     */
    void setTimeout(int ms);
    /*!
     Enables or disables to create compreesed recovery files.
     */
    void setCompressed(bool on);

protected:
    void slotCreateDocument(const App::Document& Doc);
    void slotDeleteDocument(const App::Document& Doc);
    void timerEvent(QTimerEvent * event);
    void saveDocument(const std::string&, AutoSaveProperty&);

private:
    int timeout; /*!< Timeout in milliseconds */
    bool compressed;
    std::map<std::string, AutoSaveProperty*> saverMap;
};

class RecoveryWriter : public Base::FileWriter
{
public:
    RecoveryWriter(AutoSaveProperty&);
    virtual ~RecoveryWriter();

    /*!
     This method can be re-implemented in sub-classes to avoid
     to write out certain objects. The default implementation
     always returns true.
     */
    virtual bool shouldWrite(const std::string&, const Base::Persistence *) const;
    virtual void writeFiles(void);

private:
    AutoSaveProperty& saver;
};

} //namespace Gui


#endif //GUI_AUTOSAVER_H
