/*

#NEEDREWRITE!

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
 ***************************************************************************/
//#OSDEPENDENT
#include "FCConfig.h"
#include "stdexport.h"

# include <algorithm>
# include <cassert>
# include <cstdio>
# include <cstdlib>
# include <fstream>
# include <climits>
# include <cstring>

#ifndef __cplusplus
#define __cplusplus 201703L
#endif
#include <filesystem>
namespace fs = std::filesystem;
//linux, macos
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>


#include "FileInfo.h"
#include "Exception.h"
#include "Stream.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cerrno>
#include <cstring>

using namespace Base;

#ifndef R_OK
#define R_OK    4   /* Test for read permission    */
#endif
#ifndef W_OK
#define W_OK    2   /* Test for write permission   */
#endif
#ifndef X_OK
#define X_OK    1   /* Test for execute permission */
#endif
#ifndef F_OK
#define F_OK    0   /* Test for existence          */
#endif

//**********************************************************************************
// FileInfo


FileInfo::FileInfo (const char* _FileName)
{
    setFile(_FileName);
}

FileInfo::FileInfo (const std::string &_FileName)
{
    setFile(_FileName.c_str());
}

const std::string &FileInfo::getTempPath(void){
    return (std::string) fs::temp_directory_path();
}

std::string FileInfo::getTempFileName(const char* FileName, const char* Path)
{
    //FIXME: To avoid race conditions we should rather return a file pointer
    //than a file name.
    std::string buf;

    // Path where the file is located
    if (Path)
        buf = Path;
    else
        buf = getTempPath();

    // File name in the path 
    if (FileName) {
        buf += "/";
        buf += FileName;
        buf += "XXXXXX";
    }
    else {
        buf += "/fileXXXXXX";
    }

    int id = mkstemp(const_cast<char*>(buf.c_str()));
    if (id > -1) {
        FILE* file = fdopen(id, "w");
        fclose(file);
        unlink(buf.c_str());
    }
    return buf;
}

void FileInfo::setFile(const char* name)
{
    if (!name) {
        FileName.clear();
        return;
    }

    FileName = name;

    // keep the UNC paths intact
    if (FileName.substr(0,2) == std::string("\\\\"))
        std::replace(FileName.begin()+2, FileName.end(), '\\', '/');
    else
        std::replace(FileName.begin(), FileName.end(), '\\', '/');
}

std::string FileInfo::filePath () const
{
    return FileName;
}

std::string FileInfo::fileName () const
{
    return FileName.substr(FileName.find_last_of('/')+1);
}

std::string FileInfo::dirPath () const
{
    std::size_t last_pos;
    std::string retval;
    last_pos = FileName.find_last_of('/');
    if (last_pos != std::string::npos) {
        retval = FileName.substr(0, last_pos);
    }
    else {
        char buf[PATH_MAX+1];
        const char* cwd = getcwd(buf, PATH_MAX);
        retval = std::string(cwd ? cwd : ".");
    }
    return retval;
}

std::string FileInfo::fileNamePure () const
{
    std::string temp = fileName();
    std::string::size_type pos = temp.find_last_of('.');
  
    if (pos != std::string::npos)
        return temp.substr(0,pos);
    else 
        return temp;
}


std::string FileInfo::extension () const
{
    std::string::size_type pos = FileName.find_last_of('.');
    if (pos == std::string::npos)
        return std::string();
    return FileName.substr(pos+1);
}


bool FileInfo::hasExtension (const char* Ext) const
{
    return strcasecmp(Ext,extension().c_str()) == 0;
}

bool FileInfo::exists () const
{
    return fs::exists(FileName);
}

bool FileInfo::isReadable () const
{
    return access(FileName.c_str(),R_OK) == 0;
}

bool FileInfo::isWritable () const
{
    return access(FileName.c_str(),W_OK) == 0;
}

bool FileInfo::setPermissions (Permissions perms)
{
    int mode = 0;

    if (perms & FileInfo::ReadOnly)
        mode |= S_IREAD;
    if (perms & FileInfo::WriteOnly)
        mode |= S_IWRITE;

    if (mode == 0) // bad argument
        return false;
    return chmod(FileName.c_str(),mode) == 0;
}

bool FileInfo::isFile () const
{
    if (exists()) {
        // If we can open it must be an existing file, otherwise we assume it
        // is a directory (which doesn't need to be true for any cases)
        std::ifstream str(FileName.c_str(), std::ios::in | std::ios::binary);
        if (!str) return false;
        str.close();
        return true;
    }

    return fs::is_regular_file(FileName);
}

bool FileInfo::isDir () const
{
    if (exists()) {
        // if we can chdir then it must be a directory, otherwise we assume it
        // is a file (which doesn't need to be true for any cases)
        struct stat st;
        if (stat(FileName.c_str(), &st) != 0) {
            return false;
        }
        return S_ISDIR(st.st_mode);
    }
    else
        return false;

    // TODO: Check for valid path name
    return fs::is_directory(FileName);
}

unsigned int FileInfo::size () const
{
    // not implemented
    assert(0);
    return 0;
}

TimeInfo FileInfo::lastModified() const
{
    TimeInfo ti = TimeInfo::null();
    if (exists()) {

        struct stat st;
        if (stat(FileName.c_str(), &st) == 0) {
            ti.setTime_t(st.st_mtime);
        }

    }
    return ti;
}

TimeInfo FileInfo::lastRead() const
{
    TimeInfo ti = TimeInfo::null();
    if (exists()) {

        struct stat st;
        if (stat(FileName.c_str(), &st) == 0) {
            ti.setTime_t(st.st_atime);
        }
    }
    return ti;
}

bool FileInfo::deleteFile(void) const
{
    return (::remove(FileName.c_str())==0);
}

bool FileInfo::renameFile(const char* NewName)
{
    bool res;
    res = ::rename(FileName.c_str(),NewName) == 0;
    if (!res) {
        int code = errno;
        std::clog << "Error in renameFile: " << strerror(code) << " (" << code << ")" << std::endl;
    }

    return res;
}

bool FileInfo::copyTo(const char* NewName) const
{
    FileInfo fi1(FileName);
    FileInfo fi2(NewName);
    Base::ifstream file(fi1, std::ios::in | std::ios::binary);
    Base::ofstream copy(fi2, std::ios::out | std::ios::binary);
    file >> copy.rdbuf();
    return file.is_open() && copy.is_open();
}

bool FileInfo::createDirectory(void) const
{
    return mkdir(FileName.c_str(), 0777) == 0;
}

bool FileInfo::deleteDirectory(void) const
{
    if (isDir() == false ) return false;
    return rmdir(FileName.c_str()) == 0;
}

bool FileInfo::deleteDirectoryRecursive(void) const
{
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
}

std::vector<Base::FileInfo> FileInfo::getDirectoryContent(void) const
{
    std::vector<Base::FileInfo> List;
    DIR* dp(0);
    struct dirent* dentry(0);
    if ((dp = opendir(FileName.c_str())) == NULL)
    {
        return List;
    }

    while ((dentry = readdir(dp)) != NULL)
    {
        std::string dir = dentry->d_name;
        if (dir != "." && dir != "..")
            List.push_back(FileInfo(FileName + "/" + dir));
    }
    closedir(dp);
    return List;
}
