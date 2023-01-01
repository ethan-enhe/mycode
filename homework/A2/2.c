#include <stdio.h>
int main() {
    int year;
    scanf("%d", &year);
    printf("%d年%s是闰年", year, ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? "" : "不");
    return 0;
}
