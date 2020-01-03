/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


int createSWIGPointerObj_T(const char* TypeName, void* obj, PyObject** ptr, int own)
{
    swig_module_info *module = SWIG_GetModule(NULL);
    if (!module)
        return 1;

    swig_type_info * swig_type = 0;
    swig_type = SWIG_TypeQuery(TypeName);
    if (!swig_type)
        throw Base::RuntimeError("Cannot find type information for requested type");
    
    *ptr = SWIG_NewPointerObj(obj,swig_type,own);
    if (*ptr == 0)
        throw Base::RuntimeError("Cannot convert into requested type");

    // success
    return 0;
}

int convertSWIGPointerObj_T(const char* TypeName, PyObject* obj, void** ptr, int flags)
{
    swig_module_info *module = SWIG_GetModule(NULL);
    if (!module)
        return 1;

    swig_type_info * swig_type = 0;
    swig_type = SWIG_TypeQuery(TypeName);
    if (!swig_type)
        throw Base::RuntimeError("Cannot find type information for requested type");

    // return value of 0 is on success
    if (SWIG_ConvertPtr(obj, ptr, swig_type, flags))
        throw Base::RuntimeError("Cannot convert into requested type");

    // success
    return 0;
}

void cleanupSWIG_T(const char* TypeName)
{
    swig_module_info *swig_module = SWIG_GetModule(NULL);
    if (!swig_module)
        return;

    swig_type_info * swig_type = 0;
    swig_type = SWIG_TypeQuery(TypeName);
    if (!swig_type)
        return;

    PyObject *module, *dict;
    PyObject *modules = PyImport_GetModuleDict();
    module = PyDict_GetItemString(modules, "__builtin__");
    if (module != NULL && PyModule_Check(module)) {
        dict = PyModule_GetDict(module);
        PyDict_SetItemString(dict, "_", Py_None);
    }

    module = PyDict_GetItemString(modules, "__main__");
    if (module != NULL && PyModule_Check(module)) {
        PyObject* dict = PyModule_GetDict(module);
        if (!dict) return;

        Py_ssize_t pos;
        PyObject *key, *value;
        pos = 0;
        while (PyDict_Next(dict, &pos, &key, &value)) {
            if (value != Py_None && PyUnicode_Check(key)) {
                void* ptr = 0;
                if (SWIG_ConvertPtr(value, &ptr, 0, 0) == 0)
                    PyDict_SetItem(dict, key, Py_None);
            }
        }
    }

    // Run garbage collector
    PyGC_Collect();
}
