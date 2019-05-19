/*
 * **************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2005                        *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License (LGPL)   *
 *   as published by the Free Software Foundation; either version 2 of     *
 *   the License, or (at your option) any later version.                   *
 *   for detail see the LICENCE text file.                                 *
 *                                                                         *
 *   FreeCAD is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with FreeCAD; if not, write to the Free Software        *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 *                                                                         *
 *   Juergen Riegel 2002                                                   *
 *
 *   Alexandr Parkhomenko 2019
 *   https://en.cppreference.com/w/cpp/filesystem
 ***************************************************************************/
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <cstring>
#include <filesystem>
namespace fs = std::filesystem;
#include "FileInfo.h"
#include "Exception.h"
#include "Stream.h"

using namespace Base;


FileInfo::FileInfo (const char* _FileName){
    setFile(_FileName);
}

FileInfo::FileInfo (const std::string &_FileName){
    setFile(_FileName.c_str());
}

const std::string FileInfo::getTempPath(void){
  return (std::string) fs::temp_directory_path() + "/";
}

std::string FileInfo::getTempFileName(const char* /*FileName*/, const char* Path){
  //FIXME: using FileName
  //FIXME: To avoid race conditions we should rather return a stream than a file name.
    return std::tmpnam((char*)Path);
}

void FileInfo::setFile(const char* name){
    if (!name) {
        FileName.clear();
        return;
    }
    FileName = name;
}

std::string FileInfo::filePath () const{
    return FileName;
}

std::string FileInfo::fileName () const{
    return FileName.filename();
}

std::string FileInfo::dirPath () const{
  return fs::absolute(
    FileName.parent_path()
  );
}

std::string FileInfo::fileNamePure () const{
    std::string temp = fileName();
    std::string::size_type pos = temp.find_last_of('.');
  
    if (pos != std::string::npos)
        return temp.substr(0,pos);
    else 
        return temp;
}

std::string FileInfo::extension () const{
    return FileName.extension();
}

bool FileInfo::hasExtension (const char* Ext) const{
    return strcasecmp(Ext,extension().c_str()) == 0;
}

bool FileInfo::exists () const{
    return fs::exists(FileName);
}

bool FileInfo::isReadable () const{
    return access(FileName.c_str(),R_OK) == 0;
}

bool FileInfo::isWritable () const{
    return access(FileName.c_str(),W_OK) == 0;
}

bool FileInfo::setPermissions (Permissions perms){
  fs::perms per = fs::perms::none; //fs::perms::owner_all | fs::perms::group_all
  if (perms == FileInfo::ReadOnly)
    per = fs::perms::owner_read;
  if (perms == FileInfo::WriteOnly)
    per = fs::perms::owner_write;
  if (perms == FileInfo::ReadWrite)
    per = fs::perms::owner_read & fs::perms::owner_write;
  if (per == fs::perms::none) // bad argument
    return false;
  fs::permissions(FileName, per, fs::perm_options::replace);
  return true;
}

bool FileInfo::isFile () const{
  return fs::is_regular_file(FileName);
}

bool FileInfo::isDir () const{
  if (exists()){ //overhead?
    return fs::is_directory(fs::status(FileName));
  } else
    return false;
}

unsigned int FileInfo::size () const{ // function not used
    if (!exists())
	return 0;
    try {
        fs::file_size(FileName);
    } catch(fs::filesystem_error& e) {
        std::cout << e.what() << std::endl; // filesystem error: cannot get file size: Is a directory [/dev]
    }
    return 0;
}

std::chrono::system_clock::time_point FileInfo::lastModified() const{
    return fs::last_write_time(FileName);
}

bool FileInfo::deleteFile(void) const{
    return (::remove(FileName.c_str())==0);
}

bool FileInfo::renameFile(const char* NewName){
    bool res;
    res = ::rename(FileName.c_str(),NewName) == 0;
    if (!res) {
        int code = errno;
        std::clog << "Error in renameFile: " << strerror(code) << " (" << code << ")" << std::endl;
    }
    return res;
}

bool FileInfo::copyTo(const char* NewName) const{
/*
    FileInfo fi1(FileName);
    FileInfo fi2(NewName);
    Base::ifstream file(fi1, std::ios::in | std::ios::binary);
    Base::ofstream copy(fi2, std::ios::out | std::ios::binary);
    file >> copy.rdbuf();
    return file.is_open() && copy.is_open();
*/
    try {
        fs::copy_file(FileName, NewName);
    } catch(fs::filesystem_error& e) {
        std::cout << "Could not copy \"" << FileName << "\" :" << e.what() << '\n';
        return false;
    }
    return true;
}

bool FileInfo::createDirectory(void) const {
    return fs::create_directories(FileName); //.c_str(), 0777) == 0
}
void FileInfo::currentPath(void) const {
    return fs::current_path(FileName);
}

bool FileInfo::deleteDirectory(void) const
{
    if (isDir() == false ) return false;
    std::uintmax_t n = fs::remove_all(FileName);
    std::cout << "Deleted " << n << " files or directories\n";
    return !isDir();
}

bool FileInfo::deleteDirectoryRecursive(void) const {
  return deleteDirectory();
/*
    if (isDir() == false ) return false;
    std::vector<Base::FileInfo> List = getDirectoryContent();

    for (std::vector<Base::FileInfo>::iterator It = List.begin();It!=List.end();++It) {
        if (It->isDir()) {
            It->setPermissions(FileInfo::ReadWrite);
            It->deleteDirectoryRecursive();
        }
        else if (It->isFile()) {
            It->setPermissions(FileInfo::ReadWrite);
            It->deleteFile();
        }
        else {
            throw Base::FileException("FileInfo::deleteDirectoryRecursive(): Unknown object Type in directory!");
        }
    }
    return deleteDirectory();
*/
}

std::vector<Base::FileInfo> FileInfo::getDirectoryContent(void) const {
    std::vector<Base::FileInfo> List;
    for(auto& p: fs::directory_iterator(FileName))
      List.push_back(FileInfo(p.path()));
    return List;
}
