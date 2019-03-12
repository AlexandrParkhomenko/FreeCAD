/*
for:
src/Mod/Import/App/dxf.cpp
src/App/Application.cpp
*/
#ifndef FCVERSIONS_H
#define FCVERSION_H

// Version Number
#define FCVersionMajor "${PACKAGE_VERSION_MAJOR}"
#define FCVersionMinor "${PACKAGE_VERSION_MINOR}"
#define FCVersionName  "${PACKAGE_VERSION_NAME}"
// test: $Format:Hash (%H), Date: %ci$
#define FCRevision      "${PACKAGE_WCREF}"      //Highest committed revision number
#define FCRevisionDate  "${PACKAGE_WCDATE}"     //Date of highest committed revision
#define FCRepositoryURL "${PACKAGE_WCURL}"      //Repository URL of the working copy

#endif //FCVERSION_H

