
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <structmember.h>
#include <numpy/arrayobject.h>

#include "algorithm.h"

static PyObject *
demo_fancy_algorithm(PyObject *self, PyObject *args)
{
    int err;
    PyObject *ret = NULL;
    PyObject *x = NULL;
    PyObject *y = NULL;
    PyArrayObject *x_array = NULL;
    PyArrayObject *y_array = NULL;
    PyArrayObject *result_array = NULL;
    npy_intp *shape_x, *shape_y;

    if (!PyArg_ParseTuple(args, "OO", &x, &y)) {
        goto out;
    }
    x_array = (PyArrayObject *) PyArray_FROM_OTF(x, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
    if (x_array == NULL) {
        goto out;
    }
    if (PyArray_NDIM(x_array) != 1) {
        PyErr_SetString(PyExc_ValueError, "Dim x != 1");
        goto out;
    }
    y_array = (PyArrayObject *) PyArray_FROM_OTF(y, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
    if (y_array == NULL) {
        goto out;
    }
    if (PyArray_NDIM(y_array) != 1) {
        PyErr_SetString(PyExc_ValueError, "Dim y != 1");
        goto out;
    }
    shape_x = PyArray_DIMS(x_array);
    shape_y = PyArray_DIMS(y_array);
    if (shape_x[0] != shape_y[0]) {
        PyErr_SetString(PyExc_ValueError, "x and y not same shape");
        goto out;
    }
    /* Allocate the result array */
    result_array = (PyArrayObject *) PyArray_SimpleNew(1, shape_x, NPY_FLOAT64);
    if (result_array == NULL) {
        goto out;
    }
    /* Now we can run the real calculation using pointers to the memory that
     * numpy has allocated */

    err = fancy_algorithm(
        (double *) PyArray_DATA(x_array),
        (double *) PyArray_DATA(y_array),
        (int) shape_x[0],
        (double *) PyArray_DATA(result_array));
    if (err != 0) {
        PyErr_Format(PyExc_ValueError, "Error %d occured in fancy_algorithm", err);
        goto out;
    }
    ret = (PyObject *) result_array;
    result_array = NULL;
out:
    Py_XDECREF(x_array);
    Py_XDECREF(y_array);
    Py_XDECREF(result_array);
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
    PyObject *mod = NULL;
    import_array();
    mod = PyModule_Create(&demomodule);
    return mod;
}

