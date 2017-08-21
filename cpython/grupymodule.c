// Python.h sempre vem antes de qualquer .h padrão
// Python.h já inclui alguns .h padrão (stdio, string, errno, stdlib)
#include <Python.h>

static PyObject* sum(PyObject* self, PyObject* args);
static PyObject* sum_tuple(PyObject* self, PyObject* args);

static PyObject* list_new(PyTypeObject* type, PyObject* args, PyObject* kwargs);

typedef struct {
    PyObject_HEAD
    long* head;
    long* tail;
    long* cur;
} list;

static PyTypeObject list_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "grupy.list",               /* tp_name */
    sizeof(list),               /* tp_basicsize */
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
    "grupy awesome list",       /* tp_doc */
    0,                          /* tp_traverse */
    0,                          /* tp_clear */
    0,                          /* tp_richcompare */
    0,                          /* tp_weaklistoffset */
    0,                          /* tp_iter */
    0,                          /* tp_iternext */
    0,                          /* tp_methods */
    0,                          /* tp_members */
    0,                          /* tp_base */
    0,                          /* tp_dict */
    0,                          /* tp_descr_get */
    0,                          /* tp_descr_set */
    0,                          /* tp_dictoffset */
    0,                          /* tp_init */
    0,                          /* tp_alloc */
    list_new,                   /* tp_new */
};

static PyMethodDef methods[] = {
    { "sum", sum, METH_VARARGS, "Calcula a soma de dois inteiros." },
    { "sum_tuple", sum_tuple, METH_VARARGS, "Calcula a soma dos números em uma tupla." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "grupy",
    "Doc for grupy module.",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_grupy(void) {
    PyObject* m;

    list_type.tp_new = PyType_GenericNew;

    if (PyType_Ready(&list_type) < 0) {
        return NULL;
    }

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    Py_INCREF(&list_type);
    PyModule_AddObject(m, "list", (PyObject*)&list_type);

    return m;
}

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

