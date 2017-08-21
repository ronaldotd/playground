// Python.h sempre vem antes de qualquer .h padrão
// Python.h já inclui alguns .h padrão (stdio, string, errno, stdlib)
#include <Python.h>

static PyObject* grupy_sum(PyObject* self, PyObject* args);
static PyObject* grupy_sum_tuple(PyObject* self, PyObject* args);

typedef struct {
    PyObject_HEAD
    long* head;
    long* tail;
    long* cur;
} grupy_list;

static PyTypeObject grupy_list_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "grupy.list",               /* tp_name */
    sizeof(grupy_list),         /* tp_basicsize */
    0,                          /* tp_itemsize */
    0,                          /* tp_dealloc */
    0,                          /* tp_print */
    0,                          /* tp_getattr */
    0,                          /* tp_setattr */
    0,                          /* tp_as_async */
    0,                          /* tp_repr */
    0,                          /* tp_as_number */
    0,                          /* tp_as_sequence */
    0,                          /* tp_as_mapping */
    0,                          /* tp_hash */
    0,                          /* tp_call */
    0,                          /* tp_str */
    0,                          /* tp_getattro */
    0,                          /* tp_setattro */
    0,                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,         /* tp_flags */
    "grupy awesome list"        /* tp_doc */
};

static PyMethodDef grupy_methods[] = {
    { "sum", grupy_sum, METH_VARARGS, "Calcula a soma de dois inteiros." },
    { "sum_tuple", grupy_sum_tuple, METH_VARARGS, "Calcula a soma dos números em uma tupla." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef grupy_module = {
    PyModuleDef_HEAD_INIT,
    "grupy",
    "Doc for grupy module.",
    -1,
    grupy_methods
};

PyMODINIT_FUNC PyInit_grupy(void) {
    PyObject* m;

    grupy_list_type.tp_new = PyType_GenericNew;

    if (PyType_Ready(&grupy_list_type) < 0) {
        return NULL;
    }

    m = PyModule_Create(&grupy_module);
    if (!m) {
        return NULL;
    }

    Py_INCREF(&grupy_list_type);
    PyModule_AddObject(m, "list", (PyObject*)&grupy_list_type);

    return m;
}

static PyObject* grupy_sum(PyObject* self, PyObject* args) {
    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return NULL;
    }

    return Py_BuildValue("i", x + y);
}

static PyObject* grupy_sum_tuple(PyObject* self, PyObject* args) {
    PyObject* tuple;

    if (!PyArg_ParseTuple(args, "O", &tuple)) {
        return NULL;
    }

    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_TypeError, "a função espera uma tupla");
        return NULL;
    }

    Py_ssize_t tuple_len = PyTuple_GET_SIZE(tuple);

    double sum = 0;
    for (Py_ssize_t i = 0; i < tuple_len; i++) {
        PyObject* num = PyTuple_GET_ITEM(tuple, i);
        if (!PyNumber_Check(num)) {
            PyErr_SetString(PyExc_TypeError, "tipo não numérico encontrado na tupla!");
            return NULL;
        }
        double d = PyFloat_AsDouble(num);
        sum += d;
    }

    return PyFloat_FromDouble(sum);
}

