#include <stdio.h>
#define V1 -1 
#define V2 255
#define V3 255.0
int main(){
    printf("%c,%d,%u,%x,%o,%lld,%f,%lf\n",V1,V1,V1,V1,V1,V1,V1,V1);
    printf("%c,%d,%u,%x,%o,%lld,%f,%lf\n",V2,V2,V2,V2,V2,V2,V2,V2);
    printf("%c,%d,%u,%x,%o,%lld,%f,%lf\n",V3,V3,V3,V3,V3,V3,V3,V3);
    return 0;
}
