
#include <stdio.h>
 
int main()
{
    int a = 3, b = 2;
    int quo = 0, rem = 0;
    asm("mov eax, %[a]\n\t"
        "cdq\n\t"
        "idiv %[b]\n\t"
        "mov %[quo], eax\n\t"
        "mov %[rem], edx\n\t"
        :[quo]"=m"(quo),[rem]"=m"(rem)
        :[a]"m"(a),[b]"m"(b)
        :"eax","edx","cc"
        );
    printf("result=%d,remainder=%d\n", quo, rem);
    return 0;
}
