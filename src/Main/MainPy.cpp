/***************************************************************************
 *   (c) Juergen Riegel (juergen.riegel@web.de) 2008                       *
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
//# OSDEPENDENT

#include <FCConfig.h>

# include <unistd.h> // LINUX
# include <dlfcn.h> //# LINUX

#include <stdio.h>
#include <sstream>


// FreeCAD Base header
#include <Base/Exception.h>
#include <App/Application.h>


PyMOD_INIT_FUNC(FreeCAD)
{
    // Init phase ===========================================================
    App::Application::Config()["ExeName"] = "FreeCAD";
    App::Application::Config()["ExeVendor"] = "FreeCAD";
    App::Application::Config()["AppDataSkipVendor"] = "true";

    int    argc=1;
    char** argv;
    argv = (char**)malloc(sizeof(char*)* (argc+1));

// LINUX
    putenv("LANG=C");
    putenv("LC_ALL=C");
    // get whole path of the library
    Dl_info info;
    int ret = dladdr((void*)PyInit_FreeCAD, &info);

    if ((ret == 0) || (!info.dli_fname)) {
        free(argv);
        PyErr_SetString(PyExc_ImportError, "Cannot get path of the FreeCAD module!");
        return 0;

    }

    argv[0] = (char*)malloc(PATH_MAX);
    strncpy(argv[0], info.dli_fname,PATH_MAX);
    argv[0][PATH_MAX-1] = '\0'; // ensure null termination
    // this is a workaround to avoid a crash in libuuid.so

    argv[argc] = 0;

    try {
        // Inits the Application
        App::Application::init(argc,argv);
    }
    catch (const Base::Exception& e) {
        std::string appName = App::Application::Config()["ExeName"];
        std::stringstream msg;
        msg << "While initializing " << appName << " the following exception occurred: '"
            << e.what() << "'\n\n";
        msg << "\nPlease contact the application's support team for more information.\n\n";
        printf("Initialization of %s failed:\n%s", appName.c_str(), msg.str().c_str());
    }

    free(argv[0]);
    free(argv);

    //PyObject* module = _PyImport_FindBuiltin("FreeCAD");
    PyObject* modules = PyImport_GetModuleDict();
    PyObject* module = PyDict_GetItemString(modules, "FreeCAD");
    if (!module) {
        PyErr_SetString(PyExc_ImportError, "Failed to load FreeCAD module!");
    }
    return module;

}

