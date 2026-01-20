#include <Python.h>

static PyObject *py_thereAre(PyObject *self, PyObject *args) {
    PyObject *list_obj;
    int number;

    if (!PyArg_ParseTuple(args, "Oi", &list_obj, &number)) {
        return NULL;
    }

    if (!PyList_Check(list_obj)) {
        PyErr_SetString(PyExc_TypeError, "First argument must be a list");
        return NULL;
    }

    if (number <= 0) {
        PyErr_SetString(PyExc_ValueError, "Number must be > 0");
        return NULL;
    }

    int count = 0;
    Py_ssize_t size = PyList_Size(list_obj);
    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject *item = PyList_GetItem(list_obj, i);
        int truth = PyObject_IsTrue(item);
        if (truth < 0) {
            return NULL;
        }

        if (truth) {
            if (++count > number) {
                Py_RETURN_FALSE;
            }
        }
    }

    if (count == number) {
        Py_RETURN_TRUE;
    }

    Py_RETURN_FALSE;
}

static PyMethodDef methods[] = {
    {"thereAre", py_thereAre, METH_VARARGS, "True if exactly n True valid elements in list"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "cutil",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit__thereAre(void) {
    return PyModule_Create(&module);
}
