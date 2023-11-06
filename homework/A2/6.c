#include <stdio.h>
char str[1000];
int valid(char x) { return x == '_' || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'); }
int main() {
    while (1) {
        printf("输入一串字符：");
        scanf("%s", str);
        if (str[0] == '0' && str[1] == '0' && str[2] == '0' && str[3] == '0' && str[4] == '0' && str[5] == '0') break;
        int f = valid(str[0]);
        for (int i = 1; str[i]; i++) f &= valid(str[i]) || (str[i] >= '0' && str[i] <= '9');
        if (f)
            printf("\"%s\" 是合法的 C 标识符", str);
        else
            printf("\"%s\" 不是合法的 C 标识符", str);
        puts("");
    }
    return 0;
}
