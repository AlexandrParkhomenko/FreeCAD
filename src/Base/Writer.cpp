/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#include "Writer.h"
#include "Persistence.h"
#include "Exception.h"
#include "FileInfo.h"
#include "Stream.h"
#include "Tools.h"

#include <algorithm>
#include <locale>
#include <limits>

using namespace Base;
using namespace std;

// ---------------------------------------------------------------------------
//  Writer: Constructors and Destructor
// ---------------------------------------------------------------------------

Writer::Writer(void)
  : indent(0),forceXML(false),fileVersion(1)
{
    indBuf[0] = '\0';
}

Writer::~Writer()
{
}

void Writer::insertAsciiFile(const char* FileName)
{
    Base::FileInfo fi(FileName);
    Base::ifstream from(fi);
    if (!from)
        throw Base::FileException("Writer::insertAsciiFile() Could not open file!");

    Stream() << "<![CDATA[";
    char ch;
    while (from.get(ch))
        Stream().put(ch);
    Stream() << "]]>" << endl;
}


void Writer::setForceXML(bool on)
{
    forceXML = on;
}

bool Writer::isForceXML(void)
{
    return forceXML;
}

void Writer::setFileVersion(int v)
{
    fileVersion = v;
}

int Writer::getFileVersion() const
{
    return fileVersion;
}

void Writer::setMode(const std::string& mode)
{
    Modes.insert(mode);
}

void Writer::setModes(const std::set<std::string>& modes)
{
    Modes = modes;
}

bool Writer::getMode(const std::string& mode) const
{
    std::set<std::string>::const_iterator it = Modes.find(mode);
    return (it != Modes.end());
}

std::set<std::string> Writer::getModes() const
{
    return Modes;
}

void Writer::clearMode(const std::string& mode)
{
    std::set<std::string>::iterator it = Modes.find(mode);
    if (it != Modes.end())
        Modes.erase(it);
}

void Writer::clearModes()
{
    Modes.clear();
}

void Writer::addError(const std::string& msg)
{
    Errors.push_back(msg);
}

bool Writer::hasErrors() const
{
    return (!Errors.empty());
}

void Writer::clearErrors()
{
    Errors.clear();
}

std::vector<std::string> Writer::getErrors() const
{
    return Errors;
}

std::string Writer::addFile(const char* Name,const Base::Persistence *Object)
{
    // always check isForceXML() before requesting a file!
    assert(isForceXML()==false);

    FileEntry temp;
    temp.FileName = getUniqueFileName(Name);
    temp.Object = Object;
  
    FileList.push_back(temp);

    FileNames.push_back( temp.FileName );

    // return the unique file name
    return temp.FileName;
}

std::string Writer::getUniqueFileName(const char *Name)
{
    // name in use?
    std::string CleanName = (Name ? Name : "");
    std::vector<std::string>::const_iterator pos;
    pos = find(FileNames.begin(),FileNames.end(),CleanName);

    if (pos == FileNames.end()) {
        // if not, name is OK
        return CleanName;
    }
    else {
        std::vector<std::string> names;
        names.reserve(FileNames.size());
        FileInfo fi(CleanName);
        CleanName = fi.fileNamePure();
        std::string ext = fi.extension();
        for (pos = FileNames.begin();pos != FileNames.end();++pos) {
            fi.setFile(*pos);
            std::string FileName = fi.fileNamePure();
            if (fi.extension() == ext)
                names.push_back(FileName);
        }
        std::stringstream str;
        str << Base::Tools::getUniqueName(CleanName, names);
        if (!ext.empty())
            str << "." << ext;
        return str.str();
    }
}

const std::vector<std::string>& Writer::getFilenames() const
{
    return FileNames;
}

void Writer::incInd(void)
{
    if (indent < 1020) {
        indBuf[indent  ] = ' ';
        indBuf[indent+1] = ' ';
        indBuf[indent+2] = ' ';
        indBuf[indent+3] = ' ';
        indBuf[indent+4] = '\0';
        indent += 4;
    }
}

void Writer::decInd(void)
{
    if (indent >= 4) {
        indent -= 4;
    }
    else {
        indent = 0;
    }
    indBuf[indent] = '\0';
}

FileWriter::FileWriter(const char* FileName){
  DirName = ".";
  this->FileStream.open(FileName, std::ios::out | std::ios::binary);
}

FileWriter::~FileWriter(){
}

void FileWriter::putNextEntry(const char* file)
{
    std::string fileName = file;
    this->FileStream.open(fileName.c_str(), std::ios::out | std::ios::binary);
}

//bool FileWriter::shouldWrite(const std::string& , const Base::Persistence *) const {
//    return true;
//}

void FileWriter::writeFiles(void){
    std::cout << "FileWriter::writeFiles:" << std::endl;
    // use a while loop because it is possible that while
    // processing the files new ones can be added
    size_t index = 0;
    this->FileStream.close();
    while (index < FileList.size()) {
        FileEntry entry = FileList.begin()[index];

//        if (shouldWrite(entry.FileName, entry.Object)) {
            std::string filePath = entry.FileName;
            std::string::size_type pos = 0;
            while ((pos = filePath.find("/", pos)) != std::string::npos) {
                std::string dirName = DirName + "/" + filePath.substr(0, pos);
                pos++;
                Base::FileInfo fi(dirName);
                fi.createDirectory();
            }

            std::string fileName = DirName + "/" + entry.FileName;
            std::cout << fileName << std::endl;
            this->FileStream.open(fileName.c_str(), std::ios::out | std::ios::binary);
            entry.Object->SaveDocFile(*this);
            this->FileStream.close();
//        }
        index++;
    }
}
