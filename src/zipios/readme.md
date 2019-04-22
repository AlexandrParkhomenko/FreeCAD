Introduction
   
   zipios is a java.util.zip-like C++ library for reading and
   writing Zip files. Access to individual entries is provided through
   standard C++ iostreams. A simple read-only virtual file system that
   mounts regular directories and zip files is also provided.
   
   The source code is released under the <A
   HREF="http://www.gnu.org/copyleft/lesser.html">GNU Lesser General Public
   License</A>.
   
   Status

   Spanned archives are not supported, and support is not planned.
   

   The library has been tested and appears to be working with
   <UL>
   <LI><A HREF="http://www.freebsd.org/ports/archivers.html#zipios-0.1.5">FreeBSD stable and current / gcc 2.95.3</A></LI>
   <LI>Red Hat Linux release 7.0  / gcc 2.96</LI>
   <LI>Red Hat Linux release 6.2 (Zoot) / egcs-2.91.66</LI>
   <LI>Linux Mandrake release 7.0 (Air) / gcc 2.95.2</LI>
   <LI>SGI IRIX64 6.5 / gcc 2.95.2</LI>
   <LI>SGI IRIX64 6.5 / MIPSpro Compilers: Version 7.30</LI>
   </UL>

   If you are aware of any other platforms that zipios works on,
   please let me know (thomass@deltadata.dk).

   Zip file access
   
   The two most important classes are 
   - zipfile_anchor "ZipFile" and 
   - ZipInputStream_anchor "ZipInputStream". ZipInputStream is an istream
   for reading zipfiles. It can be instantiated directly, without the
   use of ZipFile. A new ZipInputStream reads from the first entry, and
   the user can skip to the next entry by calling
   - ZipInputStream_getnextentry_anchor "ZipInputStream::getNextEntry()".
   
   ZipFile scans the central directory of a zipfile and provides an
   interface to access that directory. The user may search for entries
   with a particular filename using 
   - fcoll_getentry_anchor "ZipFile::getEntry()", 
   or simply get the complete list of entries
   with 
   - fcoll_entries_anchor "ZipFile::entries()". To get an
   istream (ZipInputStream) to a particular entry simply use
   - fcoll_getinputstream "ZipFile::getInputStream()".
   
   "example_zip.cpp" demonstrates the central elements of zipios.
   
   A Zip file appended to another file, e.g. a binary program, with the 
   program "appendzip", can be read with 
   - zipfile_openembeddedzipfile "ZipFile::openEmbeddedZipFile()".

   FileCollections
   
   A ZipFile is actually just a special kind of 
   - fcoll_anchor "FileCollection" that
   obtains its entries from a .zip Zip archive. zipios also implements
   a 
   - dircol_anchor "DirectoryCollection" that obtains its entries 
   from a specified directory, and a \ref collcoll_anchor "CollectionCollection" 
   that obtains its entries from
   other collections. Using a single CollectionCollection any number of
   other FileCollections can be placed under its control and accessed
   through the same single interface that is used to access a ZipFile or
   a DirectoryCollection. A singleton (a unique global instance)
   CollectionCollection can be obtained through
   
   - collcoll_inst_anchor "CollectionCollection::inst()" ;

   To save typing CollectionCollection has been typedef'ed to CColl. In
   the initialization part of an application FileCollections can be
   created, and placed under CColll::inst()'s control using
   
   - collcoll_addcoll_anchor "CColl::inst().addCollection()"
   
   and later an istream can be obtained using

   - fcoll_getinputstream "CColl::inst().getInputStream()".
   
   Download 
   
   Go to zipios project page on SourceForge for tar balls and ChangeLog.
   <A HREF="http://sourceforge.net/project/?group_id=5418" >
   http://sourceforge.net/project/?group_id=5418</A>
   
   Links
   
   <A HREF="ftp://ftp.freesoftware.com/pub/infozip/zlib/zlib.html">zlib</A>. 
   The compression library that zipios uses to perform the actual 
   decompression.
   
   <A HREF="http://java.sun.com/products/jdk/1.3/docs/api/index.html">
   Java 2 Platform, Standard Edition, v 1.3 API Specification
   </A>. zipios is heavily inspired by the java.util.zip package.
   
   <A
   HREF="http://www.geocities.com/SiliconValley/Lakes/2160/fformats/files/zip.txt">
   PKWARE zip format 
   </A>. A description of the zip file format.
   
   Bugs
   
   Submit bug reports and patches to thomass@deltadata.dk 
   
   
   
   Project hosted by <A HREF="http://sourceforge.net">SourceForge</A>


