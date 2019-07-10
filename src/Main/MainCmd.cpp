/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/
#include "../FCConfig.h"

#ifdef FC_OS_LINUX
# include <unistd.h>
#endif

#include <stdio.h>
#include <sstream>
#include <iostream>

// FreeCAD Base header
#include "Base/Console.h"
#include "Base/Interpreter.h"
#include "Base/Parameter.h"
#include "Base/Exception.h"
#include "Base/Factory.h"

// FreeCAD doc header
#include "App/Application.h"


using Base::Console;
using App::Application;


int main( int argc, char ** argv )
{
    // Make sure that we use '.' as decimal point
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "C");

    // Name and Version of the Application
    App::Application::Config()["ExeName"] = "FreeCAD";
    App::Application::Config()["ExeVendor"] = "FreeCAD";
    App::Application::Config()["AppDataSkipVendor"] = "true";

    try {
        // Init phase ===========================================================
        // sets the default run mode for FC, starts with command prompt if not overridden in InitConfig...
        App::Application::Config()["RunMode"] = "Exit";

        // Inits the Application
        App::Application::init(argc,argv);
    }
    catch (const Base::UnknownProgramOption& e) {
        std::cerr << e.what();
        exit(1);
    }
    catch (const Base::ProgramInformation& e) {
        std::cout << e.what();
        exit(0);
    }
    catch (const Base::Exception& e) {
        std::string appName = App::Application::Config()["ExeName"];
        std::stringstream msg;
        msg << "While initializing " << appName << " the following exception occurred: '" << e.what() << "'\n\n";
        msg << "Python is searching for its runtime files in the following directories:\n" << Py_GetPath() << "\n\n";
        msg << "Python version information:\n" << Py_GetVersion() << "\n";
        const char* pythonhome = getenv("PYTHONHOME");
        if ( pythonhome ) {
            msg << "\nThe environment variable PYTHONHOME is set to '" << pythonhome << "'.";
            msg << "\nSetting this environment variable might cause Python to fail. Please contact your administrator to unset it on your system.\n\n";
        }
        else {
            msg << "\nPlease contact the application's support team for more information.\n\n";
        }

        printf("Initialization of %s failed:\n%s", appName.c_str(), msg.str().c_str());
        exit(100);
    }
    catch (...) {
        std::string appName = App::Application::Config()["ExeName"];
        std::stringstream msg;
        msg << "Unknown runtime error occurred while initializing " << appName <<".\n\n";
        msg << "Please contact the application's support team for more information.\n\n";
        printf("Initialization of %s failed:\n%s", appName.c_str(), msg.str().c_str());
        exit(101);
    }

    // Run phase ===========================================================
    try {
        Application::runApplication();
    }
    catch (const Base::SystemExitException &e) {
        exit(e.getExitCode());
    }
    catch (const Base::Exception& e) {
        e.ReportException();
        exit(1);
    }
    catch (...) {
        Console().Error("Application unexpectedly terminated\n");
        exit(1);
    }

    // Destruction phase ===========================================================
    Console().Log("FreeCAD terminating...\n");

    try {
        // close open documents
        App::GetApplication().closeAllDocuments();
    }
    catch(...) {
    }

    // cleans up
    Application::destruct();

    Console().Log("FreeCAD completely terminated\n");

    return 0;
}

