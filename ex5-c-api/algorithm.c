
int
fancy_algorithm(double x, double y, double *result)
{
    int ret = 0;

    /* Some arbitrary checks on the input values */
    if (x < 0) {
        ret = -1; /* We would really have symbolic constants here */
        goto out;
    }
    /* Input checks are ok, run our 'fancy' algorithm. */

    *result = x * y;
out:
    return ret;
}
