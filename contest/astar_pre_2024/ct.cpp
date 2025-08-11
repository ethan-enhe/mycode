#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
int main() {
    for (ll i = 1; i <= 100; i++) {
        system("./gen.exe>test.in");
        system("./E.exe<test.in>1.out");
        system("./force.exe<test.in>2.out");
        if (system("diff 1.out 2.out")) {
            break;
        }
        cout << i << endl;
    }
    return 0;
}
