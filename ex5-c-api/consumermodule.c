#include <Python.h>
#include "demomodule.h"

static PyObject *
consumer_fancy_algorithm(PyObject *self, PyObject *args)
{
    PyObject *ret = NULL;
    double x, y, result;
    int err;

    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        goto out;
    }
    printf("consumer running fancy_algorithm\n");
    err = fancy_algorithm(x, y, &result);
    if (err != 0) {
        PyErr_Format(PyExc_ValueError, "Error %d occured in fancy_algorithm", err);
        goto out;
    }
    ret = Py_BuildValue("d", result);
out:
    return ret;
}

static PyMethodDef consumer_methods[] = {
    {"fancy_algorithm", (PyCFunction) consumer_fancy_algorithm, METH_VARARGS,
         "Runs an algorithm defined in another Python module.."},
    {NULL, NULL, 0, NULL}   /* sentinel */
};

static struct PyModuleDef consumermodule = {
    PyModuleDef_HEAD_INIT,
    "consumer",
    NULL,
    -1,
    consumer_methods
};

PyMODINIT_FUNC
PyInit_consumer(void)
{
    PyObject *m;

    m = PyModule_Create(&consumermodule);
    if (m == NULL) {
        goto out;
    }
    if (import_demo() < 0) {
        return NULL;
    }
out:
    return m;
}
