
#include <bits/stdc++.h>

#include <cstdlib>
#define sys(fmt...) (sprintf(tmp, fmt), system(tmp))
using namespace std;
const int MXS = 10000;
char tmp[MXS];
int main(int argc, char *argv[]) {
    for (int i = 1; i <= 1000; i++) {
        system("./gen 1000000000 100000 1000000>1.in");
        system("./std<1.in>s.out");
        /* system("./force<1.in>f.out"); */
        /* if (system("diff f.out s.out")) { */
        /*     break; */
        /* } */
        system("cat s.out");
        cout<<i<<endl;
    }
    return 0;
}
