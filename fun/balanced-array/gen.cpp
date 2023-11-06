#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;
int main(int argc, char **argv) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    registerGen(argc, argv, 1);
    int mxn = opt<int>(1);
    int mxw = opt<int>(2);
    // int concentrate = opt<int>(3);
    rnd.setSeed(opt<int>(3));
    int n = rnd.wnext(1, mxn, 3);
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        // if(rnd.next(1,100)<=1)cout<<rnd.next(1,mxw)
        cout << rnd.wnext(1, mxw, -rnd.wnext(0, mxw, 5));
        if (i < n) cout << ' ';
    }
    cout << '\n';
    return 0;
}
