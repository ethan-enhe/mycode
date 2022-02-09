#include <bits/stdc++.h>
using namespace std;
#define vec vector
using pi = pair<int, int>;
using vi = vec<int>;
using vvi = vec<vi>;
const char nl = '\n';
const int ZERO = 1e8 + 5, INF = ZERO << 1, LG = log2(INF);
int n, m, vecc;
unordered_map<int, int> rt;
vvi data;
void ins(vi &x, int y) { x.insert(upper_bound(x.begin(), x.end(), y), y); }
void ers(vi &x, int y) { x.erase(lower_bound(x.begin(), x.end(), y)); }
int rngc(vi &x, int l, int r) { return upper_bound(x.begin(), x.end(), r) - lower_bound(x.begin(), x.end(), l); }
void mod(int i, int v, bool tp) {
    v += ZERO;
    for (; v <= INF; v += v & (-v)) {
        int &ind = rt[v];
        if (!ind) ind = ++vecc;
        tp ? ins(data[ind], i) : ers(data[ind], i);
    }
}
int qrk(int ql, int qr, int qv) {
    int r = 1;
    qv += ZERO - 1;
    for (; qv; qv ^= qv & (-qv)) {
        auto it = rt.find(qv);
        if (it != rt.end()) r += rngc(data[it->second], ql, qr);
    }
    return r;
}
int qva(int ql, int qr, int qrk) {
    if (qrk <= 0) return -numeric_limits<int>::max();
    if (qrk > qr - ql + 1) return numeric_limits<int>::max();
    int r = 0;
    for (int w = 1 << LG; w; w >>= 1)
        if (r + w <= INF) {
            auto it = rt.find(r + w);
            int delt = it == rt.end() ? 0 : rngc(data[it->second], ql, qr);
            if (qrk > delt) {
                r += w;
                qrk -= delt;
            }
        }
    return r + 1 - ZERO;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    data.resize((n + m) * log2(INF));
    vi arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        mod(i, arr[i], 1);
    }
    while (m--) {
        int opt, a, b, c;
        cin >> opt >> a >> b;
        if (opt != 3) cin >> c;

        if (opt == 1)
            cout << qrk(a, b, c) << nl;
        else if (opt == 2)
            cout << qva(a, b, c) << nl;
        else if (opt == 3) {
            mod(a, arr[a], 0);
            mod(a, arr[a] = b, 1);
        } else if (opt == 4)
            cout << qva(a, b, qrk(a, b, c) - 1) << nl;
        else
            cout << qva(a, b, qrk(a, b, c + 1)) << nl;
    }

    return 0;
}
