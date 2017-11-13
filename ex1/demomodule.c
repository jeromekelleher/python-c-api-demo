#include <Python.h>

static PyObject *
demo_add(PyObject *self, PyObject *args)
{
    PyObject *ret = NULL;
    double x, y, result;

    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        goto out;
    }
    result = x + y;
    ret = Py_BuildValue("d", result);
out:
    return ret;
}

static PyMethodDef demo_methods[] = {
    {"add", (PyCFunction) demo_add, METH_VARARGS,
         "Print a lovely skit to standard output."},
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
