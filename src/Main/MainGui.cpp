/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *   
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/
#include <FCConfig.h>

#include <unistd.h> //LINUX

#include <map>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QLocale>
#include <QTextCodec>

// FreeCAD header
#include "Base/Console.h"
#include "Base/Interpreter.h"
#include "Base/Parameter.h"
#include "Base/Exception.h"
#include "Base/Factory.h"
#include "App/Application.h"
#include "Gui/BitmapFactory.h"
#include "Gui/Application.h"

class Redirection
{
public:
    Redirection(FILE* f)
        : fi(Base::FileInfo::getTempFileName()), file(f)
    {
        FILE* ptr = freopen(fi.filePath().c_str(),"w",file);
        if (!ptr) {
            std::cerr << "Failed to reopen file" << std::endl;
        }
    }
    ~Redirection()
    {
        fclose(file);
        fi.deleteFile();
    }

private:
    Base::FileInfo fi;
    FILE* file;
};

QString myDecoderFunc(const QByteArray &localFileName)
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    return codec->toUnicode(localFileName);
}

QByteArray myEncoderFunc(const QString &fileName)
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    return codec->fromUnicode(fileName);
}

int main( int argc, char ** argv )
{
    // Make sure to setup the Qt locale system before setting LANG and LC_ALL to C.
    // which is needed to use the system locale settings.
    (void)QLocale::system();    // See https://forum.freecadweb.org/viewtopic.php?f=18&t=20600
    // See Gui::Application::runApplication()
    putenv("LC_NUMERIC=C");
    putenv("PYTHONPATH=");
    // Name and Version of the Application
    App::Application::Config()["ExeName"] = "FreeCAD";
    App::Application::Config()["ExeVendor"] = "FreeCAD";
    App::Application::Config()["AppDataSkipVendor"] = "true";

    // set the banner (for logging and console)
    App::Application::Config()["AppIcon"] = "freecad";
    App::Application::Config()["StartWorkbench"] = "Sketcher";

    try {
        // Init phase ===========================================================
        // sets the default run mode for FC, starts with gui if not overridden in InitConfig...
        App::Application::Config()["RunMode"] = "Gui";
        App::Application::Config()["Console"] = "0";

        // Inits the Application 
        App::Application::init(argc, argv);
        std::map<std::string, std::string>::iterator it = App::Application::Config().find("NavigationStyle");
        if (it != App::Application::Config().end()) {
            ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
            // if not already defined do it now (for the very first start)
            std::string style = hGrp->GetASCII("NavigationStyle", it->second.c_str());
            hGrp->SetASCII("NavigationStyle", style.c_str());
        }
        Gui::Application::initApplication();

        // Only if 'RunMode' is set to 'Gui' do the replacement
        if (App::Application::Config()["RunMode"] == "Gui")
            Base::Interpreter().replaceStdOutput();
    }
    catch (const Base::UnknownProgramOption& e) {
        QApplication app(argc,argv);
        QString appName = QString::fromLatin1(App::Application::Config()["ExeName"].c_str());
        QString msg = QString::fromLatin1(e.what());
        QString s = QLatin1String("<pre>") + msg + QLatin1String("</pre>");
        QMessageBox::critical(0, appName, s);
        exit(1);
    }
    catch (const Base::ProgramInformation& e) {
        QApplication app(argc,argv);
        QString appName = QString::fromLatin1(App::Application::Config()["ExeName"].c_str());
        QString msg = QString::fromUtf8(e.what());
        QString s = QLatin1String("<pre>") + msg + QLatin1String("</pre>");

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle(appName);
        msgBox.setDetailedText(msg);
        msgBox.setText(s);
        msgBox.exec();
        exit(0);
    }
    catch (const Base::Exception& e) {
        // Popup an own dialog box instead of that one of Windows
        QApplication app(argc,argv);
        QString appName = QString::fromLatin1(App::Application::Config()["ExeName"].c_str());
        QString msg;
        msg = QObject::tr("While initializing %1 the following exception occurred: '%2'\n\n"
                          "Python is searching for its files in the following directories:\n%3\n\n"
                          "Python version information:\n%4\n")
                          .arg(appName, QString::fromUtf8(e.what()),
                          QString::fromUtf8(Py_EncodeLocale(Py_GetPath(),NULL)), QString::fromLatin1(Py_GetVersion()));
        const char* pythonhome = getenv("PYTHONHOME");
        if (pythonhome) {
            msg += QObject::tr("\nThe environment variable PYTHONHOME is set to '%1'.")
                .arg(QString::fromUtf8(pythonhome));
            msg += QObject::tr("\nSetting this environment variable might cause Python to fail. "
                "Please contact your administrator to unset it on your system.\n\n");
        } else {
            msg += QObject::tr("\nPlease contact the application's support team for more information.\n\n");
        }

        QMessageBox::critical(0, QObject::tr("Initialization of %1 failed").arg(appName), msg);
        exit(100);
    }
    catch (...) {
        // Popup an own dialog box instead of that one of Windows
        QApplication app(argc,argv);
        QString appName = QString::fromLatin1(App::Application::Config()["ExeName"].c_str());
        QString msg = QObject::tr("Unknown runtime error occurred while initializing %1.\n\n"
                                  "Please contact the application's support team for more information.\n\n").arg(appName);
        QMessageBox::critical(0, QObject::tr("Initialization of %1 failed").arg(appName), msg);
        exit(101);
    }

    // Run phase ===========================================================
    /*
    Base::RedirectStdOutput stdcout;
    Base::RedirectStdLog    stdclog;
    Base::RedirectStdError  stdcerr;
    std::streambuf* oldcout = std::cout.rdbuf(&stdcout);
    std::streambuf* oldclog = std::clog.rdbuf(&stdclog);
    std::streambuf* oldcerr = std::cerr.rdbuf(&stdcerr);
*/
   // try {
        // if console option is set then run in cmd mode
        if (App::Application::Config()["Console"] == "1")
            App::Application::runApplication();
        if (App::Application::Config()["RunMode"] == "Gui" ||
            App::Application::Config()["RunMode"] == "Internal"){
            Gui::Application::runApplication();
        }
        else {
            App::Application::runApplication();
        }
 /*   }
    catch (const Base::SystemExitException& e) {
        exit(e.getExitCode());
    }
    catch (const Base::Exception& e) {
        e.ReportException();
        std::cout << "exit(1)" << std::endl;
        exit(1);
    }
    catch (...) {
	std::cerr << "exit(1) Application unexpectedly terminated" << std::endl;
        exit(1);
    } */
/*
    std::cout.rdbuf(oldcout);
    std::clog.rdbuf(oldclog);
    std::cerr.rdbuf(oldcerr);
*/
    // Destruction phase ===========================================================
    Base::Console().Log("%s terminating...\n",App::Application::Config()["ExeName"].c_str());

    // cleans up 
    App::Application::destruct();

    Base::Console().Log("%s completely terminated\n",App::Application::Config()["ExeName"].c_str());

    return 0;
}
