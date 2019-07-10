/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002 2005                   *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_FILEINFO_H
#define BASE_FILEINFO_H

#include <filesystem>
namespace fs = std::filesystem;
#include <chrono>

#include "stdexport.h"
#include <string>
#include <vector>
#include "Base/TimeInfo.h"


namespace Base
{

/** File name unification
  * This class handles everything related to file names
  * the file names are internal generally UTF-8 encoded on
  * all platforms.
  */
class BaseExport FileInfo
{
public:
    enum Permissions {
        WriteOnly = 0x01,
        ReadOnly = 0x02,
        ReadWrite = 0x03,
    };

    /// Constrction
    FileInfo (const char* _FileName="");
    FileInfo (const std::string &_FileName);
    /// Set a new file name
    void setFile(const char* name);
    /// Set a new file name
    void setFile(const std::string &name){setFile(name.c_str());}


    /** @name extraction of information */
    //@{
    /// Returns the file name, including the path (which may be absolute or relative).
    std::string filePath () const;
    /// Returns the dir path name (which may be absolute or relative).
    std::string dirPath () const;
    /// Returns the name of the file, excluding the path, including the extension.
    std::string fileName () const;
    /// Returns the name of the file, excluding the path and the extension.
    std::string fileNamePure () const;
    /** Returns the extension of the file.
     * The extension consists of all characters in the file after (but not including)
     * the last '.' character.
     *@code
     *  FileInfo fi( "/tmp/archive.tar.gz" );
     *  ext = fi.extension();   // ext = "gz"
     *@endcode
     */
    std::string extension () const;
    /// Checks for a special extension, NOT case sensetive
    bool hasExtension (const char* Ext) const;
    //@}

    /** @name methods to test the status of the file or dir */
    //@{
    /// Does the file exist?
    bool exists () const;
    /// Checks if the file exist and is readable
    bool isReadable () const;
    /// Checks if the file exist and is writable
    bool isWritable () const;
    /// Tries to set the file permisson
    bool setPermissions (Permissions);
    /// Checks if it is a file (not a direrctory)
    bool isFile () const;
    /// Checks if it is a directory (not a file)
    bool isDir () const;
    /// The size of the file 
    unsigned int size () const;
    /// Returns the time when the file was last modified.
    std::filesystem::file_time_type lastModified() const;
    //@}

    /** @name Directory management*/
    //@{
    /// Creates a directory. Returns true if successful; otherwise returns false.
    bool createDirectory( void ) const;
    void currentPath( void ) const;
    /// Get a list of the directory content
    std::vector<Base::FileInfo> getDirectoryContent(void) const;
    /// Delete an empty directory 
    bool deleteDirectory(void) const;
    /// Delete a directory and all its content.
    bool deleteDirectoryRecursive(void) const;
    //@}

    /// Delete the file
    bool deleteFile(void) const;
    /// Rename the file
    bool renameFile(const char* NewName);
    /// Rename the file
    bool copyTo(const char* NewName) const;

    /** @name Tools */
    //@{
    /// Get a unique File Name in the given or (if 0) in the temp path
    static std::string getTempFileName(const char* FileName=0, const char* path=0);
    /// Get the path to the dir which is considered to temp files
    static const std::string getTempPath(void);
    //@}

protected:
    fs::path FileName;
};

} //namespace Base


#endif // BASE_FILEINFO_H

