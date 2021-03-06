#include <Python.h>

static PyObject* foo(PyObject* self, PyObject* args) {
    Py_RETURN_NONE;
}

static PyObject* sum(PyObject* self, PyObject* args) {
    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return NULL;
    }

    return Py_BuildValue("i", x + y);
}

static PyMethodDef methods[] = {
    { "foo", foo, METH_NOARGS, "Test method." },
    { "sum", sum, METH_VARARGS, "Calculate the sum of two integers." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,      // must always be PyModuleDef_HEAD_INIT
    "grupy",                    // module name
    "Doc for grupy2 module.",   // module docstring
    -1,                         // module memory area size
    methods                     // table of module-level functions
};

PyMODINIT_FUNC PyInit_grupy2(void) {
    PyObject* m;

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    return m;
}

