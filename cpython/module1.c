#include <Python.h>

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "grupy",
    "Doc for grupy1 module.",
    -1
};

PyMODINIT_FUNC PyInit_grupy1(void) {
    PyObject* m;

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    return m;
}


