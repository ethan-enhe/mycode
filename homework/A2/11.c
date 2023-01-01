#include <math.h>
#include <stdio.h>
double integral(double l, double r, double step, double (*f)(double)) {
    double ans = 0, lastf = f(l);
    while (1) {
        if (l + step < r) {
            l += step;
            double nxf = f(l);
            ans += (nxf + lastf) / 2 * step;
            lastf = nxf;
        } else {
            ans += (f(r) + lastf) / 2 * (r - l);
            return ans;
        }
    }
}
int main() {
    double l, r, step;
    puts("l r step");
    scanf("%lf %lf %lf", &l, &r, &step);
    printf("%f", integral(l, r, step, cos));
    return 0;
}
