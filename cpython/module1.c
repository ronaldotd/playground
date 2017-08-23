#include <Python.h>

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,      // must always be PyModuleDef_HEAD_INIT
    "grupy",                    // module name
    "Doc for grupy1 module.",   // module docstring
    -1                          // module memory area size
};

PyMODINIT_FUNC PyInit_grupy1(void) {
    PyObject* m;

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    return m;
}


