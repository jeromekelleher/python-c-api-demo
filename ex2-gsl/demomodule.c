#include <Python.h>
#include <gsl/gsl_sf_coulomb.h>

/* Wrapper for GSL function gsl_sf_hydrogenicR,
 * https://www.gnu.org/software/gsl/doc/html/specfunc.html#normalized-hydrogenic-bound-states
 */
static PyObject *
demo_hydrogenicR(PyObject *self, PyObject *args)
{
    PyObject *ret = NULL;
    double n, l, Z, r, result;

    if (!PyArg_ParseTuple(args, "dddd", &n, &l, &Z, &r)) {
        goto out;
    }
    if (n <= l) {
        PyErr_SetString(PyExc_ValueError, "n must be >= l");
        goto out;
    }
    /* Check bounds on other input parameters */

    result = gsl_sf_hydrogenicR(n, l, Z, r);
    ret = Py_BuildValue("d", result);
out:
    return ret;
}

static PyMethodDef demo_methods[] = {
    {"hydrogenicR", (PyCFunction) demo_hydrogenicR, METH_VARARGS,
         "Returns the result of gsl_sf_hydrogenicR"},
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
