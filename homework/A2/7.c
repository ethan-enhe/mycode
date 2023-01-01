#include <stdio.h>
#include <stdlib.h>
typedef struct obj {
    int id;
    double w, v;
} obj;

#define MXN 100
obj arr[MXN];
int n;
double totv;

int sgn(double x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}
int cmpw(const void* x, const void* y) { return sgn(((obj*)y)->w - ((obj*)x)->w); }
int cmpw_v(const void* x, const void* y) { return sgn(((obj*)y)->w / ((obj*)y)->v - ((obj*)x)->w / ((obj*)x)->v); }
double min(double x, double y) { return x < y ? x : y; }

int main() {
    printf("背包体积：");
    scanf("%lf", &totv);
    printf("物品数量：");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("输入第 %d 个物体的价值，体积：", i);
        scanf("%lf%lf", &arr[i].w, &arr[i].v);
        arr[i].id = i;
    }
    puts("---");

    puts("0-1背包 按价值贪心");
    qsort(arr + 1, n, sizeof(obj), cmpw);
    double curv = totv, curw = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i].v <= curv) {
            printf("放入 %d 号 体积： %.3f 价值： %.3f\n", arr[i].id, arr[i].v, arr[i].w);
            curw += arr[i].w;
            curv -= arr[i].v;
        }
    }
    printf("总价值 %.3f: \n", curw);
    puts("---");

    puts("0-1背包 按单位体积价值贪心");
    qsort(arr + 1, n, sizeof(obj), cmpw_v);
    curv = totv, curw = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i].v <= curv) {
            printf("放入 %d 号 体积： %.3f 价值： %.3f\n", arr[i].id, arr[i].v, arr[i].w);
            curw += arr[i].w;
            curv -= arr[i].v;
        }
    }
    printf("总价值 %.3f: \n", curw);
    puts("---");

    puts("部分背包 按单位体积价值贪心");
    curv = totv, curw = 0;
    for (int i = 1; i <= n; i++) {
        if (curv < 1e-6) break;
        double delt = min(arr[i].v, curv);
        printf("放入 %d 号 原体积： %.3f 原价值： %.3f\n", arr[i].id, arr[i].v, arr[i].w);
        printf("放入体积： %.3f 放入价值： %.3f\n", delt, delt * arr[i].w / arr[i].v);
        curw += delt * arr[i].w / arr[i].v;
        curv -= delt;
    }
    printf("总价值 %.3f: \n", curw);
    return 0;
}
