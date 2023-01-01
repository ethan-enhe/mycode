#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int _dpm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int y, m, d;
int isrun() { return y % 4 == 0 && y % 100 != 0; }
int dpm(int month) {
    if (month == 2) return _dpm[month] + isrun();
    return _dpm[month];
}
int main() {
    puts("输入年月日：");
    scanf("%d %d %d", &y, &m, &d);
    for (int i = 1; i < m; i++) d += dpm(i);
    printf("是本年的第 %d 天", d);
    return 0;
}
