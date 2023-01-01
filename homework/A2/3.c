#include <stdio.h>
int main() {
    char x;
    while ((x = getchar()) != EOF) {
        if(x=='0')break;
        if (x >= 'a' && x <= 'z') {
            putchar(x + 'A' - 'a');
            putchar('\n');
        } else if (x >= 'A' && x <= 'Z') {
            printf("\'%c\' 已经是大写字母\n", x);
        } else
            printf("\'%c\' 不是字母\n", x);
    }
    return 0;
}
