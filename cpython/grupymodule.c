// Python.h sempre vem antes de qualquer .h padrão
// Python.h já inclui alguns .h padrão (stdio, string, errno, stdlib)
#include <Python.h>

struct node {
    int val;
    struct node* next;
};

typedef struct {
    PyObject_HEAD
    struct node* head;
    struct node* tail;
    struct node* cur;
    int len;
} list;

static PyObject* sum(PyObject* self, PyObject* args);
static PyObject* sum_tuple(PyObject* self, PyObject* args);

static int list_init(list* self, PyObject* args, PyObject* kwargs);
static PyObject* list_append(list* self, PyObject* args);
static PyObject* list_str(list* self);
static PyObject* list_iter(list* self);
static PyObject* list_iternext(list* self);

static PyMethodDef list_methods[] = {
    { "append", (PyCFunction)list_append, METH_VARARGS, "Append an element to the list." },
    { NULL }
};

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
    (reprfunc)list_str,         /* tp_repr */
    0,                          /* tp_as_number */
    0,                          /* tp_as_sequence */
    0,                          /* tp_as_mapping */
    0,                          /* tp_hash */
    0,                          /* tp_call */
    (reprfunc)list_str,         /* tp_str */
    0,                          /* tp_getattro */
    0,                          /* tp_setattro */
    0,                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,         /* tp_flags */
    "grupy awesome list",       /* tp_doc */
    0,                          /* tp_traverse */
    0,                          /* tp_clear */
    0,                          /* tp_richcompare */
    0,                          /* tp_weaklistoffset */
    (getiterfunc)list_iter,     /* tp_iter */
    (iternextfunc)list_iternext,/* tp_iternext */
    list_methods,               /* tp_methods */
    0,                          /* tp_members */
    0,                          /* tp_getset */
    0,                          /* tp_base */
    0,                          /* tp_dict */
    0,                          /* tp_descr_get */
    0,                          /* tp_descr_set */
    0,                          /* tp_dictoffset */
    (initproc)list_init,        /* tp_init */
    0,                          /* tp_alloc */
    0,                          /* tp_new */
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


static int list_init(list* self, PyObject* args, PyObject* kwargs) {
    self->head = NULL;
    self->tail = NULL;
    self->cur = NULL;
    self->len = 0;

    return 0;
}

static PyObject* list_append(list* self, PyObject* args) {
    int elem;

    if (!PyArg_ParseTuple(args, "i", &elem)) {
        return NULL;
    }

    struct node* new_node = malloc(sizeof(struct node));
    new_node->val = elem;
    new_node->next = NULL;

    if (!self->head) {
        self->head = new_node;
        self->tail = self->head;
    }
    else {
        self->tail->next = new_node;
        self->tail = new_node;
    }

    self->len++;

    Py_RETURN_NONE;
}

static PyObject* list_str(list* self) {
    return PyUnicode_FromFormat("list object with %d elements", self->len);
}

static PyObject* list_iter(list* self) {
    printf("list_iter\n");
    Py_INCREF(self);
    self->cur = self->head;
    return (PyObject*)self;
}

static PyObject* list_iternext(list* self) {
    printf("list_iternext\n");
    if (self->cur) {
        PyObject* ret = Py_BuildValue("i", self->cur->val);
        self->cur = self->cur->next;
        return ret;
    }
    else {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
}
