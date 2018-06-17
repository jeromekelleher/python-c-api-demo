#include <Python.h>
#include "algorithm.h"

static PyObject *
demo_fancy_algorithm(PyObject *self, PyObject *args)
{
    PyObject *ret = NULL;
    double x, y, result;
    int err;

    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        goto out;
    }
    err = fancy_algorithm(x, y, &result);
    if (err != 0) {
        PyErr_Format(PyExc_ValueError, "Error %d occured in fancy_algorithm", err);
        goto out;
    }
    ret = Py_BuildValue("d", result);
out:
    return ret;
}

static PyMethodDef demo_methods[] = {
    {"fancy_algorithm", (PyCFunction) demo_fancy_algorithm, METH_VARARGS,
         "Runs an algorithm defined in a local C file."},
    {NULL, NULL, 0, NULL}   /* sentinel */
};

static struct PyModuleDef demomodule = {
    PyModuleDef_HEAD_INIT,
    "demo",
    NULL,
    -1,
    demo_methods
};

PyMODINIT_FUNC
PyInit_demo(void)
{
    return PyModule_Create(&demomodule);
}
