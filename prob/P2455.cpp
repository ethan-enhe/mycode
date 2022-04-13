#include <bits/stdc++.h>

using namespace std;
using db = double;
using eq = vector<db>;

const int MXN = 55;
const double EPS = 1e-9;

bool is0(db x) { return fabs(x) <= EPS; }
eq mj[MXN];

void eli(eq &x, const eq &y, int ind) {
    if (is0(x[ind])) return;
    double rate = x[ind] / y[ind];
    for (int i = 0; i <= ind; i++) x[i] -= y[i] * rate;
}
int ins(eq &x) {
    for (int i = x.size() - 1; ~i; i--)
        if (!is0(x[i])) {
            if (mj[i].empty()) {
                mj[i] = x;
                return i;
            } else
                eli(x, mj[i], i);
        }
    return -1;
}
db getx(int ind) {
    eq x = mj[ind];
    for (int i = ind - 1; i; i--)
        if (!is0(x[i])) eli(x, mj[i], i);
    return x[0] / x[ind];
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    eq arr(n + 1);
    bool hasinf = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> arr[j];
        cin >> arr[0];
        int ret = ins(arr);
        if (!ret) return cout << -1, 0;
        if (ret == -1) hasinf = 1;
    }
    if (hasinf) return cout << 0, 0;
    for (int i = 1; i <= n; i++) cout << 'x' << i << '=' << fixed << setprecision(2) << getx(i) << '\n';

    return 0;
}
