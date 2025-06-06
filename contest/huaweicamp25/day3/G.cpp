#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll r, n;
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r;
    ll lf = 0, rt = r;
    cin >> n;
    while (n--) {
        ll d;
        cin >> d;
        lf += d, rt += d;
        lf = min(max(lf, 0ll), r);
        rt = min(max(rt, 0ll), r);
    }
    if (lf == rt) {
        cout << lf;
    } else
        cout << "uncertain";
    return 0;
}
