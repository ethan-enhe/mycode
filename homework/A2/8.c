#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    FILE *fd = NULL, *fr = NULL;
    fd = fopen("data.txt", "r");
    if (fd == NULL) {
        fd = fopen("data.txt", "w");
        printf("有几个数:");
        int n;
        scanf("%d", &n);
        printf("输入 %d 个数：", n);
        for (int i = 1; i <= n; i++) {
            double x;
            scanf("%lf", &x);
            fprintf(fd, "%f ", x);
        }
    } else {
        fr = fopen("result.txt", "a");
        time_t curt = time(0);
        fprintf(fr, "%s", ctime(&curt));
        printf("输入几个数:");
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            double x;
            fscanf(fd, "%lf", &x);
            fprintf(fr, "%f ", x);
        }
        fprintf(fr, "\n");
    }
    if (fd) fclose(fd);
    if (fr) fclose(fr);
    return 0;
}
