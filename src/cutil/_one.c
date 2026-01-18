#include <Python.h>

static PyObject *py_one(PyObject *self, PyObject *args) {
    PyObject *list;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list))
        return NULL;

    Py_ssize_t n = PyList_GET_SIZE(list);
    int count = 0;

    for (Py_ssize_t i = 0; i < n; i++) {
        PyObject *item = PyList_GET_ITEM(list, i);

        int truth = PyObject_IsTrue(item);
        if (truth < 0) {
            // error during __bool__ o __len__
            return NULL;
        }

        if (truth) {
            if (++count > 1)
                Py_RETURN_FALSE;
        }
    }

    if (count == 1)
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}


static PyMethodDef methods[] = {
    {"one", py_one, METH_VARARGS, "True if exactly one True in list"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "cutil",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit__one(void) {
    return PyModule_Create(&module);
}
