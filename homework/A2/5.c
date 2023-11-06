#include <stdio.h>
int main() {
    // x^2-y=0
    int c1 = 0, c2 = 0;
    double x;
    printf("输入近似解：");
    scanf("%lf", &x);
    while (1) {
        double nx = x - (3 * x * x * x - 3 * x * x + x - 6) / (9 * x * x - 6 * x + 1);
        if (nx - x <= 1e-6 && x - nx <= 1e-6) break;
        ++c1;
        x = nx;
    }
    printf("%.6f 次数： %d\n", x, c1);

    double l, r;
    printf("输入范围：");
    scanf("%lf%lf", &l, &r);
    while (l + 1e-6 < r) {
        double mid = (l + r) / 2;
        if (3 * mid * mid * mid - 3 * mid * mid + mid - 6 > 0)
            r = mid;
        else
            l = mid;
        ++c2;
    }
    printf("%.6f 次数： %d", l, c2);

    return 0;
}
