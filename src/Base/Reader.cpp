/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <xercesc/sax/SAXParseException.hpp>
# include <xercesc/sax/SAXException.hpp>
# include <xercesc/sax2/XMLReaderFactory.hpp>
# include <xercesc/sax2/SAX2XMLReader.hpp>

#include <locale>
#include <filesystem>
namespace fs = std::filesystem;

#include "Reader.h"
#include "Exception.h"
#include "Persistence.h"
#include "InputSource.h"
#include "Console.h"
#include "Sequencer.h"


#include "XMLTools.h"


XERCES_CPP_NAMESPACE_USE
using namespace std;
// ---------------------------------------------------------------------------
//  Base::XMLReader: Constructors and Destructor
// ---------------------------------------------------------------------------

Base::XMLReader::XMLReader(const char* FileName, std::istream& str)
  : DocumentSchema(0), ProgramVersion(""), FileVersion(0), Level(0),
    CharacterCount(0), ReadType(None), _File(FileName), _valid(false),
    _verbose(true)
{
    //FIXME: Check whether this is correct
    str.imbue(std::locale::classic());

    // create the parser
    parser = XMLReaderFactory::createXMLReader();

    parser->setContentHandler(this);
    parser->setLexicalHandler(this);
    parser->setErrorHandler(this);

    try {
        StdInputSource file(str, _File.filePath().c_str());
        _valid = parser->parseFirst(file, token);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
    }
#ifndef FC_DEBUG
    catch (...) {
        cerr << "Unexpected Exception \n";
    }
#endif
}

Base::XMLReader::~XMLReader()
{
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    delete parser;
}

const char* Base::XMLReader::localName(void) const
{
    return LocalName.c_str();
}

unsigned int Base::XMLReader::getAttributeCount(void) const
{
    return (unsigned int)AttrMap.size();
}

long Base::XMLReader::getAttributeAsInteger(const char* AttrName) const
{
    AttrMapType::const_iterator pos = AttrMap.find(AttrName);

    if (pos != AttrMap.end())
        return atol(pos->second.c_str());
    else
        // wrong name, use hasAttribute if not sure!
        assert(0);

    return 0;
}

unsigned long Base::XMLReader::getAttributeAsUnsigned(const char* AttrName) const
{
    AttrMapType::const_iterator pos = AttrMap.find(AttrName);

    if (pos != AttrMap.end())
        return strtoul(pos->second.c_str(),0,10);
    else
        // wrong name, use hasAttribute if not sure!
        assert(0);

    return 0;
}

double Base::XMLReader::getAttributeAsFloat  (const char* AttrName) const
{
    AttrMapType::const_iterator pos = AttrMap.find(AttrName);

    if (pos != AttrMap.end())
        return atof(pos->second.c_str());
    else
        // wrong name, use hasAttribute if not sure!
        assert(0);

    return 0.0;
}

const char*  Base::XMLReader::getAttribute (const char* AttrName) const
{
    AttrMapType::const_iterator pos = AttrMap.find(AttrName);

    if (pos != AttrMap.end()) {
        return pos->second.c_str();
    }
    else {
        // wrong name, use hasAttribute if not sure!
        std::ostringstream msg;
        msg << "XML Attribute: \"" << AttrName << "\" not found";
        throw Base::XMLAttributeError(msg.str());
    }
}

bool Base::XMLReader::hasAttribute (const char* AttrName) const
{
    return AttrMap.find(AttrName) != AttrMap.end();
}

bool Base::XMLReader::read(void)
{
    ReadType = None;

    try {
        parser->parseNext(token);
    }
    catch (const XMLException& toCatch) {
#if 0
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return false;
#else
        char* message = XMLString::transcode(toCatch.getMessage());
        std::string what = message;
        XMLString::release(&message);
        throw Base::XMLBaseException(what);
#endif
    }
    catch (const SAXParseException& toCatch) {
#if 0
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return false;
#else
        char* message = XMLString::transcode(toCatch.getMessage());
        std::string what = message;
        XMLString::release(&message);
        throw Base::XMLParseException(what);
#endif
    }
    catch (...) {
#if 0
        cerr << "Unexpected Exception \n" ;
        return false;
#else
        throw Base::XMLBaseException("Unexpected XML exception");
#endif
    }

    return true;
}

void Base::XMLReader::readElement(const char* ElementName)
{
    bool ok;
    int currentLevel = Level;
    std::string currentName = LocalName;
    do {
        ok = read(); if (!ok) break;
        if (ReadType == EndElement && currentName == LocalName && currentLevel >= Level) {
            // we have reached the end of the element when calling this method
            // thus we must stop reading on.
            break;
        }
        else if (ReadType == EndDocument) {
            // the end of the document has been reached but we still try to continue on reading
            throw Base::XMLParseException("End of document reached");
        }
    } while ((ReadType != StartElement && ReadType != StartEndElement) ||
             (ElementName && LocalName != ElementName));
}

void Base::XMLReader::readEndElement(const char* ElementName)
{
    // if we are already at the end of the current element
    if (ReadType == EndElement && LocalName == ElementName) {
        return;
    }
    else if (ReadType == EndDocument) {
        // the end of the document has been reached but we still try to continue on reading
        throw Base::XMLParseException("End of document reached");
    }

    bool ok;
    do {
        ok = read(); if (!ok) break;
        if (ReadType == EndDocument)
            break;
    } while (ReadType != EndElement || (ElementName && LocalName != ElementName));
}

void Base::XMLReader::readCharacters(void)
{
}

void Base::XMLReader::readFiles() const{
	fs::path mycurrentpath = fs::current_path();
	fs::current_path(
//  fs::absolute(
//      ((fs::path)this->_File.currentPath()).parent_path()
//    )
      this->_File.dirPath()
  );
  std::cout << "Base::XMLReader::readFiles() fs::current_path(): " << fs::current_path() << endl;
  for(auto& FileName: fs::directory_iterator(".")){ // need entry
    std::cout << FileName.path() << endl;

    FileInfo fi1(FileName.path());
    FileEntry fe1;
    fe1.FileName = FileName.path();
    if(fi1.isFile ()){
      std::ifstream file(fe1.FileName, std::ios::in | std::ios::binary);
      try {
        Base::Reader reader(file, FileName.path(), FileVersion);
        //fe1.Object->RestoreDocFile(reader);
      }
      catch(...) {
        // For any exception we just continue with the next file.
        // It doesn't matter if the last reader has read more or
        // less data than the file size would allow.
        // All what we need to do is to notify the user about the
        // failure.
        Base::Console().Error("Reading failed from embedded file: %s\n", FileName.path().c_str());
      }
    }
  }
	fs::current_path(mycurrentpath);
}

/**/
/*
void Base::XMLReader::readFiles() const //zipios::ZipInputStream &zipstream
{
//#1  0x7fa54fc1d27c in Base::XMLReader::readFiles() const from lib/libFreeCADBase.so+0x70c
//#2  0x7fa54fe22327 in App::Document::restore() from           lib/libFreeCADApp.so+0x377
//#3  0x7fa54ff3a45e in App::Application::openDocument(char const*) from lib/libFreeCADApp.so+0x20e
//#4  0x7fa54ff51ea5 in App::Application::sOpenDocument(_object*, _object*) from lib/libFreeCADApp.so+0xa5

    // It's possible that not all objects inside the document could be created, e.g. if a module
    // is missing that would know these object types. So, there may be data files inside the zip
    // file that cannot be read. We simply ignore these files.
    // On the other hand, however, it could happen that a file should be read that is not part of
    // the zip file. This happens e.g. if a document is written without GUI up but is read with GUI
    // up. In this case the associated GUI document asks for its file which is not part of the ZIP
    // file, then.
    // In either case it's guaranteed that the order of the files is kept.

	fs::path mycurrentpath = fs::current_path();
    fs::current_path(
        this->_File.filePath()
    );
    std::cout << "Base::XMLReader::readFiles() fs::current_path(): " << fs::current_path() << endl;
    size_t FileList_size = 0;
    std::vector<FileEntry> _FileList;
    std::vector<std::string> _FileNames;
    std::vector<std::string> fl = {
    		"./GuiDocument.xml",
    		"./PartShape.brp",
    		"./PartShape1..brp",
    		"./Job.nc",
    		"./pickle",
    		"./Operations.nc",
    		"./pickle1",
    		"./pickle2",
    		"./pickle3",
    		"./pickle4",
    		"./PartShape1..brp",
    		"./Default_Tool.nc",
    		"./pickle5",
    		"./pickle6",
    		"./PartShape1..brp",
    		"./Contour.nc",
    		"./pickle7",
    		"./PartShape1..brp",
    		"./DiffuseColor",
    		"./LineColorArray",
    		"./PointColorArray",
    		"./pickle8",
    		"./pickle9",
    		"./pickle10",
    		"./DiffuseColor1",
    		"./LineColorArray1",
    		"./PointColorArray1",
    		"./pickle11",
    		"./DiffuseColor2",
    		"./LineColorArray2",
    		"./PointColorArray2",
    		"./pickle12",
    		"./pickle13",
    		"./DiffuseColor3",
    		"./LineColorArray3",
    		"./PointColorArray3",
    		"./pickle14",
    		"./pickle15"
    };
    for(auto& FileName: fs::directory_iterator(".")){
    	//for(auto const& FileName: fl) {
    	FileList_size++;
//
//    	const char* epta = FileName.path().c_str();
//    	Base::Persistence *Object;

//    	this->addFile(epta, Object); //(const char* Name, Base::Persistence *Object)
//
        FileEntry temp;
        temp.FileName = FileName.path().c_str();
        temp.Object = nullptr;//Object;

        _FileList.push_back(temp);
        _FileNames.push_back( temp.FileName );
    	//this->FileList = {};//.push_back({FileName.path(),0});
    	//FileNames.push_back((std::string)FileName.path());
    	//break;
    }
    if (FileList_size == 0) return;
    //FileList = _FileList;
    //FileNames = _FileNames;

    std::vector<FileEntry>::const_iterator it = _FileList.begin();
    Base::SequencerLauncher seq("Importing project files...", FileList_size);

    ///for(auto& FileName: fs::directory_iterator(".")){
    while (it != _FileList.end()) {
        std::vector<FileEntry>::const_iterator jt = it;
        // Check if the current entry is registered, otherwise check the next registered files as soon as
        // both file names match
        while (jt != _FileList.end() && it->FileName != jt->FileName)
            ++jt;
        // If this condition is true both file names match and we can read-in the data, otherwise
        // no file name for the current entry in the zip was registered.
        if (jt != _FileList.end()) {
            //try {
            //    Base::Reader reader(zipstream, jt->FileName, FileVersion);
            //   jt->Object->RestoreDocFile(reader);
            //    if (reader.getLocalReader())
            //        reader.getLocalReader()->readFiles(zipstream);
            //}
            ////FileInfo fi1(FileName.path());
            ////if(fi1.isFile ()){
                std::cout << jt->FileName << std::endl;
              std::ifstream file(jt->FileName, std::ios::in | std::ios::binary);
              try {
                Base::Reader reader(file, jt->FileName, FileVersion);
                //jt->Object->RestoreDocFile(reader);
              }
            catch(...) {
                // For any exception we just continue with the next file.
                // It doesn't matter if the last reader has read more or
                // less data than the file size would allow.
                // All what we need to do is to notify the user about the
                // failure.
                Base::Console().Error("Reading failed from embedded file: %s\n", jt->FileName);
            }
            ////}
            // Go to the next registered file name
            it = jt + 1;
        }

        seq.next();
    //}
    }
	fs::current_path(mycurrentpath);
}
*/
const char *Base::XMLReader::addFile(const char* Name, Base::Persistence *Object)
{
    FileEntry temp;
    temp.FileName = Name;
    temp.Object = Object;

    FileList.push_back(temp);
    FileNames.push_back( temp.FileName );

    return Name;
}

const std::vector<std::string>& Base::XMLReader::getFilenames() const
{
    return FileNames;
}

bool Base::XMLReader::isRegistered(Base::Persistence *Object) const
{
    if (Object) {
        for (std::vector<FileEntry>::const_iterator it = FileList.begin(); it != FileList.end(); ++it) {
            if (it->Object == Object)
                return true;
        }
    }

    return false;
}

void Base::XMLReader::addName(const char*, const char*)
{
}

const char* Base::XMLReader::getName(const char* name) const
{
    return name;
}

bool Base::XMLReader::doNameMapping() const
{
    return false;
}

// ---------------------------------------------------------------------------
//  Base::XMLReader: Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void Base::XMLReader::startDocument()
{
    ReadType = StartDocument;
}

void Base::XMLReader::endDocument()
{
    ReadType = EndDocument;
}

void Base::XMLReader::startElement(const XMLCh* const /*uri*/, const XMLCh* const localname, const XMLCh* const /*qname*/, const XERCES_CPP_NAMESPACE_QUALIFIER Attributes& attrs)
{
    Level++; // new scope
    LocalName = StrX(localname).c_str();

    // saving attributes of the current scope, delete all previously stored ones
    AttrMap.clear();
    for (unsigned int i = 0; i < attrs.getLength(); i++) {
        AttrMap[StrX(attrs.getQName(i)).c_str()] = StrXUTF8(attrs.getValue(i)).c_str();
    }

    ReadType = StartElement;
}

void Base::XMLReader::endElement  (const XMLCh* const /*uri*/, const XMLCh *const localname, const XMLCh *const /*qname*/)
{
    Level--; // end of scope
    LocalName = StrX(localname).c_str();

    if (ReadType == StartElement)
        ReadType = StartEndElement;
    else
        ReadType = EndElement;
}

void Base::XMLReader::startCDATA ()
{
    ReadType = StartCDATA;
}

void Base::XMLReader::endCDATA ()
{
    ReadType = EndCDATA;
}

#if (XERCES_VERSION_MAJOR == 2)
void Base::XMLReader::characters(const   XMLCh* const chars, const unsigned int length)
#else
void Base::XMLReader::characters(const   XMLCh* const chars, const XMLSize_t length)
#endif
{
    Characters = StrX(chars).c_str();
    ReadType = Chars;
    CharacterCount += length;
}

#if (XERCES_VERSION_MAJOR == 2)
void Base::XMLReader::ignorableWhitespace( const   XMLCh* const /*chars*/, const unsigned int /*length*/)
#else
void Base::XMLReader::ignorableWhitespace( const   XMLCh* const /*chars*/, const XMLSize_t /*length*/)
#endif
{
    //fSpaceCount += length;
}

void Base::XMLReader::resetDocument()
{
    //fAttrCount = 0;
    //fCharacterCount = 0;
    //fElementCount = 0;
    //fSpaceCount = 0;
}


// ---------------------------------------------------------------------------
//  Base::XMLReader: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void Base::XMLReader::error(const XERCES_CPP_NAMESPACE_QUALIFIER SAXParseException& e)
{
    // print some details to error output and throw an
    // exception to abort the parsing
    cerr << "Error at file " << StrX(e.getSystemId())
         << ", line " << e.getLineNumber()
         << ", char " << e.getColumnNumber() << endl;
    throw e;
}

void Base::XMLReader::fatalError(const XERCES_CPP_NAMESPACE_QUALIFIER SAXParseException& e)
{
    // print some details to error output and throw an
    // exception to abort the parsing
    cerr << "Fatal Error at file " << StrX(e.getSystemId())
         << ", line " << e.getLineNumber()
         << ", char " << e.getColumnNumber() << endl;
    throw e;
}

void Base::XMLReader::warning(const XERCES_CPP_NAMESPACE_QUALIFIER SAXParseException& e)
{
    // print some details to error output and throw an
    // exception to abort the parsing
   cerr << "Warning at file " << StrX(e.getSystemId())
        << ", line " << e.getLineNumber()
        << ", char " << e.getColumnNumber() << endl;
   throw e;
}

void Base::XMLReader::resetErrors()
{
}

bool Base::XMLReader::testStatus(ReaderStatus pos) const
{
    return StatusBits.test((size_t)pos);
}

void Base::XMLReader::setStatus(ReaderStatus pos, bool on)
{
    StatusBits.set((size_t)pos, on);
}

void Base::XMLReader::setPartialRestore(bool on)
{
    setStatus(PartialRestore, on);
    setStatus(PartialRestoreInDocumentObject, on);
    setStatus(PartialRestoreInProperty, on);
    setStatus(PartialRestoreInObject, on);
}

void Base::XMLReader::clearPartialRestoreDocumentObject(void)
{
    setStatus(PartialRestoreInDocumentObject, false);
    setStatus(PartialRestoreInProperty, false);
    setStatus(PartialRestoreInObject, false);
}

void Base::XMLReader::clearPartialRestoreProperty(void)
{
    setStatus(PartialRestoreInProperty, false);
    setStatus(PartialRestoreInObject, false);
}

void Base::XMLReader::clearPartialRestoreObject(void)
{
    setStatus(PartialRestoreInObject, false);
}

// ----------------------------------------------------------

Base::Reader::Reader(std::istream& str, const std::string& name, int version)
  : std::istream(str.rdbuf()), _str(str), _name(name), fileVersion(version)
{
}

std::string Base::Reader::getFileName() const
{
    return this->_name;
}

int Base::Reader::getFileVersion() const
{
    return fileVersion;
}

std::istream& Base::Reader::getStream()
{
    return this->_str;
}

