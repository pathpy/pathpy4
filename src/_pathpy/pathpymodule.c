#include "preamble.h"

#include "pathpypath.h"


#define PATHPY_MODULE

#define MODULE_DOCS \
  "Low-level Python interface for the pathpy library. " \
  "Should not be used directly.\n"

/**
 * Module definition table
 */
static struct PyModuleDef cpathpy_module = {
    PyModuleDef_HEAD_INIT,
    "pathpy._pathpy",                           /* m_name */
    NULL,                                       /* m_doc */
    -1,                                         /* m_size */
    NULL,                                       /* m_methods */
    NULL,                                       /* m_reload */
    NULL,                                       /* m_traverse */
    NULL,                                       /* m_clear */
    NULL                                        /* m_free */
};

PyMODINIT_FUNC
PyInit__pathpy(void) {
    PyObject* m;

    /* 'Ready' the type. This copies functions and data down from our subclass
       so that `pathpymodule_PathPyPath_Type` is in a valid state. */
    if (PyType_Ready(&pathpymodule_PathPyPath_Type)) {
      /* failed to ready the type */
      return NULL;
    }

    if (!(m = PyModule_Create(&cpathpy_module))) {
        /* failed to allocate the module object */
        return NULL;
    }

    if (PyModule_AddObject(m, "PathPyPath",
                           (PyObject*) &pathpymodule_PathPyPath_Type)) {
        /* failed to store PathPyPath on the module */
        Py_DECREF(&pathpymodule_PathPyPath_Type);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
