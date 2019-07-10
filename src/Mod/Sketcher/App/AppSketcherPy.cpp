/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel (juergen.riegel@web.de)              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <BRepPrimAPI_MakeBox.hxx>
# include <TopoDS_Face.hxx>
# include <Geom_Plane.hxx>

#include "Base/Console.h"
#include "Base/PyObjectBase.h"
#include "Base/Exception.h"
#include "Base/FileInfo.h"
#include "App/Application.h"
#include "App/Document.h"

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

// Things from the part module
#include "Mod/Part/App/TopoShape.h"
#include "Mod/Part/App/TopoShapePy.h"

#include "SketchObjectSF.h"


namespace Sketcher {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("Sketcher")
    {
        add_varargs_method("open",&Module::open
        );
        add_varargs_method("insert",&Module::insert
        );
        initialize("This module is the Sketcher module."); // register with Python
    }

    virtual ~Module() {}

private:
    Py::Object open(const Py::Tuple& args)
    {
        char* Name;
        if (!PyArg_ParseTuple(args.ptr(), "et","utf-8",&Name))
            throw Py::Exception();
        std::string EncodedName = std::string(Name);
        PyMem_Free(Name);

        //Base::Console().Log("Open in Part with %s",Name);
        Base::FileInfo file(EncodedName.c_str());

        // extract extension
        if (file.extension().empty())
            throw Py::RuntimeError("No file extension");

        throw Py::RuntimeError("Unknown file extension");
      //return Py::None();
    }

    Py::Object insert(const Py::Tuple& args)
    {
        char* Name;
        const char* DocName;
        if (!PyArg_ParseTuple(args.ptr(), "ets","utf-8",&Name,&DocName))
            throw Py::Exception();
        std::string EncodedName = std::string(Name);
        PyMem_Free(Name);

        try {
            //Base::Console().Log("Insert in Part with %s",Name);
            Base::FileInfo file(EncodedName.c_str());

            // extract extension
            if (file.extension().empty())
                throw Py::RuntimeError("No file extension");

            App::Document *pcDoc = App::GetApplication().getDocument(DocName);
            if (!pcDoc) {
                pcDoc = App::GetApplication().newDocument(DocName);
            }

            if (file.hasExtension(".skf")) {
                Sketcher::SketchObjectSF *pcFeature = (Sketcher::SketchObjectSF *)pcDoc->addObject("Sketcher::SketchObjectSF",file.fileNamePure().c_str());
                pcFeature->SketchFlatFile.setValue(EncodedName.c_str());

                pcDoc->recompute();
            }
            else {
                throw Py::RuntimeError("Unknown file extension");
            }
        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }
        return Py::None();
    }
};

/// @cond DOXERR
PyObject* initModule()
{
    return (new Module())->module().ptr();
}
/// @endcond

} // namespace Sketcher
