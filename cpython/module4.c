#include <Python.h>

struct stack {
    PyObject_HEAD
    int len;
};

static PyObject* stack_push(PyObject* self, PyObject* args) {
    struct stack* stack = (struct stack*) self;
    stack->len++;
    Py_RETURN_NONE;
}

static PyObject* stack_pop(PyObject* self, PyObject* args) {
    struct stack* stack = (struct stack*) self;
    if (stack->len) {
        stack->len--;
    }
    Py_RETURN_NONE;
}


static PyMethodDef stack_methods[] = {
    { "push", stack_push, METH_VARARGS, "Push a number to the stack." },
    { "pop", stack_pop, METH_VARARGS, "Pop a number from the stack." },
    { NULL, NULL, 0, NULL }
};

static int stack_init(PyObject* self, PyObject* args, PyObject* kwargs) {
    struct stack* stack = (struct stack*) self;
    stack->len = 0;
    return 0;
}

static PyObject* stack_str(PyObject* self) {
    struct stack* stack = (struct stack*) self;
    return PyUnicode_FromFormat("Stack length is %d", stack->len);
}

static PyTypeObject stack_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "grupy.Stack",              /* tp_name */
    sizeof(struct stack),       /* tp_basicsize */
    0,                          /* tp_itemsize */
    NULL,                       /* tp_dealloc */
    NULL,                       /* tp_print */
    NULL,                       /* tp_getattr */
    NULL,                       /* tp_setattr */
    NULL,                       /* tp_as_async */
    NULL,                       /* tp_repr */
    NULL,                       /* tp_as_number */
    NULL,                       /* tp_as_sequence */
    NULL,                       /* tp_as_mapping */
    NULL,                       /* tp_hash */
    NULL,                       /* tp_call */
    (reprfunc)stack_str,        /* tp_str */
    NULL,                       /* tp_getattro */
    NULL,                       /* tp_setattro */
    NULL,                       /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,         /* tp_flags */
    "Grupy awesome stack",      /* tp_doc */
    NULL,                       /* tp_traverse */
    NULL,                       /* tp_clear */
    NULL,                       /* tp_richcompare */
    0,                          /* tp_weaklistoffset */
    NULL,                       /* tp_iter */
    NULL,                       /* tp_iternext */
    stack_methods,              /* tp_methods */
    NULL,                       /* tp_members */
    NULL,                       /* tp_getset */
    NULL,                       /* tp_base */
    NULL,                       /* tp_dict */
    NULL,                       /* tp_descr_get */
    NULL,                       /* tp_descr_set */
    0,                          /* tp_dictoffset */
    (initproc)stack_init,       /* tp_init */
    NULL,                       /* tp_alloc */
    NULL,                       /* tp_new */
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "grupy",
    "Doc for grupy4 module.",
    -1
};

PyMODINIT_FUNC PyInit_grupy4(void) {
    PyObject* m;

    stack_type.tp_new = PyType_GenericNew;

    if (PyType_Ready(&stack_type) < 0) {
        return NULL;
    }

    m = PyModule_Create(&module);
    if (!m) {
        return NULL;
    }

    Py_INCREF(&stack_type);
    PyModule_AddObject(m, "Stack", (PyObject*)&stack_type);

    return m;
}

