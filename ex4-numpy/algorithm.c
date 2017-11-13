
#include <stdlib.h>

int
fancy_algorithm(double *x, double *y, int n, double *result)
{
    int ret = 0;

    if (x == NULL || y == NULL || result == NULL) {
        ret = -2;
        goto out;
    }

    /* Do a simple componentwise multiply. This could be anything though */
    for (int j = 0; j < (int) n; j++) {
        result[j] = x[j] * y[j];
    }
out:
    return ret;
}
