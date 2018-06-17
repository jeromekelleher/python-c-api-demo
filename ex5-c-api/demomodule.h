#ifndef Py_DEMOMODULE_H
#define Py_DEMOMODULE_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEMO_MODULE

#include "algorithm.h"

#else

static void **demo_API;

/* int fancy_algorithm(double x, double y, double *result); */
#define fancy_algorithm\
    (*(int (*)(double x, double y, double *result)) demo_API[0])


/* Return -1 on error, 0 on success.
 * PyCapsule_Import will set an exception if there's an error.
 */
static int
import_demo(void)
{
    demo_API = (void **)PyCapsule_Import("demo._C_API", 0);
    return (demo_API != NULL) ? 0 : -1;
}

#endif

#ifdef __cplusplus
}
#endif
#endif
