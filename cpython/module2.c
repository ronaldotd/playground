#include <Python.h>

static PyObject* sum(PyObject* self, PyObject* args) {
    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return NULL;
    }

    return Py_BuildValue("i", x + y);
}

static PyMethodDef methods[] = {
    { "sum", sum, METH_VARARGS, "Calculate the sum of two integers." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "grupy",
    "Doc for grupy2 module.",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_grupy2(void) {
    PyObject* m;

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    return m;
}

