#include <stdio.h>
typedef struct comp {
    double real, imag;
} comp;
comp mult(comp x, comp y) {
    comp res;
    res.real = x.real * y.real - x.imag * y.imag;
    res.imag = x.real * y.imag + x.imag * y.real;
    return res;
}
int main() {
    comp a, b, c;
    scanf("%lf%lf%lf%lf", &a.real, &a.imag, &b.real, &b.imag);
    c=mult(a, b);
    printf("%f + %f i",c.real,c.imag);
    return 0;
}
