/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_PROPERTFILE_H
#define APP_PROPERTFILE_H


#include "stdexport.h"
#include <string>
#include <list>
#include <vector>
#include <boost/filesystem/path.hpp>

#include "PropertyStandard.h"


namespace Base {
class Writer;
}

namespace App
{

/** File properties
  * This property holds a file name
  */
class AppExport PropertyFile : public PropertyString
{
    TYPESYSTEM_HEADER();

public:
    PropertyFile(void);
    virtual ~PropertyFile();
    
    virtual const char* getEditorName(void) const
    { return "Gui::PropertyEditor::PropertyFileItem"; }
};

/** File include properties
  * This property doesn't only save the file name like PropertyFile
  * it also includes the file itself into the document. The file
  * doesn't get loaded into memory, it gets copied from the document
  * archive into the document transient directory. There it is accessible for
  * the algorithms. You get the transient path through getDocTransientPath()
  * It's allowed to read the file, it's not allowed to write the file
  * directly in the transient path! That would undermine the Undo/Redo
  * framework. It's only allowed to use setValue() to change the file.
  * If you give a file name outside the transient dir to setValue() it
  * will copy the file. If you give a file name in the transient path it
  * will just rename and use the same file. You can use getExchangeTempFile() to 
  * get a file name in the transient dir to write a new file version.
 */
class AppExport PropertyFileIncluded : public Property
{
    TYPESYSTEM_HEADER();

public:
    PropertyFileIncluded(void);
    virtual ~PropertyFileIncluded();

    void setValue(const char* sFile, const char* sName=0);
    const char* getValue(void) const;

    virtual const char* getEditorName(void) const
    { return "Gui::PropertyEditor::PropertyTransientFileItem"; }
    virtual PyObject *getPyObject(void);
    virtual void setPyObject(PyObject *);
    
    virtual void Save (Base::Writer &writer) const;
    virtual void Restore(Base::XMLReader &reader);

    virtual void SaveDocFile (Base::Writer &writer) const;
    virtual void RestoreDocFile(Base::Reader &reader);

    virtual Property *Copy(void) const;
    virtual void Paste(const Property &from);
    virtual unsigned int getMemSize (void) const;

    /** get a temp file name in the transient path of the document.
      * Using this file for new Version of the file and set 
      * this file with setValue() is the fastest way to change
      * the File.
      */
    std::string getExchangeTempFile(void) const;
    std::string getOriginalFileName(void) const;

protected:
    // get the transient path if the property is in a DocumentObject
    std::string getDocTransientPath(void) const;
    std::string getUniqueFileName(const std::string&, const std::string&) const;
    void aboutToSetValue(void);

protected:
    mutable std::string _cValue;
    mutable std::string _BaseFileName;
    mutable std::string _OriginalName;
};


} // namespace App

#endif // APP_PROPERTFILE_H
