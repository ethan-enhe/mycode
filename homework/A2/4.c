#include <stdio.h>
int main() {
    // x^2-y=0
    double x, y, nx;
    scanf("%lf", &y);
    x = y;
    while (1) {
        nx = x - (x * x - y) / 2 / x;
        if (nx - x <= 1e-6 && x - nx <= 1e-6) break;
        x = nx;
    }
    printf("%.6f", x);

    return 0;
}
