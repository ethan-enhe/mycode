#include <stdio.h>
#define getsize(type) printf("sizeof(" #type ") = %lu\n", sizeof(type))
int main() {
    getsize(long long);
    getsize(long double);
    getsize(1);
    getsize('a');
    getsize(1.0);
    return 0;
}
