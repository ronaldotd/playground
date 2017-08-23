#include <Python.h>

static PyObject* sum(PyObject* self, PyObject* args) {
    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return NULL;
    }

    return Py_BuildValue("i", x + y);
}

static PyObject* sum_tuple(PyObject* self, PyObject* args) {
    PyObject* tuple;

    if (!PyArg_ParseTuple(args, "O", &tuple)) {
        return NULL;
    }

    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_TypeError, "function expects a tuple");
        return NULL;
    }

    Py_ssize_t tuple_len = PyTuple_GET_SIZE(tuple);

    double sum = 0;
    for (Py_ssize_t i = 0; i < tuple_len; i++) {
        PyObject* num = PyTuple_GET_ITEM(tuple, i);
        if (!PyNumber_Check(num)) {
            PyErr_SetString(PyExc_TypeError, "non-numeric type found in tuple");
            return NULL;
        }
        double d = PyFloat_AsDouble(num);
        sum += d;
    }

    return PyFloat_FromDouble(sum);
}

static PyMethodDef methods[] = {
    { "sum", sum, METH_VARARGS, "Calculate the sum of two integers." },
    { "sum_tuple", sum_tuple, METH_VARARGS, "Calculate the sum of all integers in a tuple." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,      // must always be PyModuleDef_HEAD_INIT
    "grupy",                    // module name
    "Doc for grupy3 module.",   // module docstring
    -1,                         // module memory area size
    methods                     // table of module-level functions
};

PyMODINIT_FUNC PyInit_grupy3(void) {
    PyObject* m;

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    return m;
}

