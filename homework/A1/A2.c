#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
int main() {
    /* printf("%lf", DBL_MIN); */
    printf("char_max = %d\n", CHAR_MAX);
    printf("char_min = %d\n", CHAR_MIN);
    printf("unsigned char_max = %d\n", UCHAR_MAX);
    printf("long_max = %ld\n", LONG_MAX);
    printf("long_min = %ld\n", LONG_MIN);
    printf("double_max = %e\n", DBL_MAX);
    printf("double_0- = %e\n", -DBL_MIN);
    printf("double_0+ = %e\n", DBL_MIN);
    printf("double_min = %e\n", -DBL_MAX);
    assert(DBL_MIN != 0.);

    /* printf("%lf\n",DBL_MIN); */
    return 0;
}
