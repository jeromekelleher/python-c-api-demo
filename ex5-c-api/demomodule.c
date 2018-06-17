#include <Python.h>
#define DEMO_MODULE
#include "demomodule.h"

static PyObject *
demo_fancy_algorithm(PyObject *self, PyObject *args)
{
    PyObject *ret = NULL;
    double x, y, result;
    int err;

    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        goto out;
    }
    printf("demo running fancy_algorithm\n");
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
    PyObject *m;
    static void *demo_API[1];
    PyObject *c_api_object;

    m = PyModule_Create(&demomodule);
    if (m == NULL) {
        goto out;
    }

    /* Initialize the C API pointer array */
    demo_API[0] = (void *) fancy_algorithm;

    /* Create a Capsule containing the API pointer array's address */
    c_api_object = PyCapsule_New((void *)demo_API, "demo._C_API", NULL);

    if (c_api_object != NULL) {
        PyModule_AddObject(m, "_C_API", c_api_object);
    }
out:
    return m;
}
