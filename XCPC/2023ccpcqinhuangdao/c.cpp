#include <bits/stdc++.h>

#include <vector>

using namespace std;
const char nl = '\n';
const int INF = 1e9;
const int MXN = 1e6 + 5;
const int P1 = 1e9 + 7;
const int P2 = 998244353;

int n, m;
char arr[MXN];

struct mod {
    int x, y;
    mod operator+(const mod &b) const { return {(x + b.x) % P1, (y + b.y) % P2}; }
    mod operator*(const mod &b) const { return {(int)((1ll * x * b.x) % P1), (int)((1ll * y * b.y) % P2)}; }
    mod operator-(const mod &b) const { return {(x + P1 - b.x) % P1, (y + P2 - b.y) % P2}; }
    bool operator==(const mod &b) const { return x == b.x && y == b.y; }
} pw[MXN], h[MXN], rh[MXN];
const mod BASE = {131, 147};
void init() {
    pw[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * BASE;
        h[i] = h[i - 1] * BASE + mod{arr[i], arr[i]};
        // cerr<<h[i].x<<endl;
    }
    for (int i = n; i; i--) {
        rh[i] = rh[i + 1] * BASE + mod{arr[i], arr[i]};
        // cerr<<rh[i].x<<endl;
    }
}
mod hsh(int l, int r) { return h[r] - h[l - 1] * pw[r - l + 1]; }
mod rhsh(int l, int r) { return rh[l] - rh[r + 1] * pw[r - l + 1]; }
// int pl[MXN], pr[MXN];
int rad[MXN];
int ql[MXN], qr[MXN], lcp[MXN], ans[MXN], cnt[MXN];

vector<int> pr[MXN], pl[MXN];
vector<int> ask1[MXN], ask2[MXN];

void solve(int i, int l, int r) {
    ql[i] = l, qr[i] = r;
    int lcpl = 0, lcpr = r - l + 1;
    while (lcpl < lcpr) {
        int mid = (lcpl + lcpr + 1) >> 1;
        if (hsh(l, l + mid - 1) == rhsh(r - mid + 1, r))
            lcpl = mid;
        else
            lcpr = mid - 1;
    }
    if (lcpl * 2 >= r - l + 1) {
        ans[i] = cnt[i] = 0;
    } else {
        lcp[i] = lcpl;
        ask1[l + lcpl].push_back(i);
        ask2[r - lcpl].push_back(i);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> n >> s >> m;
    arr[n = 1] = '$';
    for (auto c : s) {
        arr[++n] = c;
        arr[++n] = '$';
    }
    init();
    cerr << (arr + 1) << endl;
    // cerr << hsh(1, 2).x << " " << rhsh(2, 3).x << endl;
    // cerr << (hsh(2, 4).x) << rhsh(2, 4).x << endl;

    for (int i = 1; i <= n; i++) {
        int l = 0, r = min(i - 1, n - i);
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (hsh(i - mid, i + mid) == rhsh(i - mid, i + mid))
                l = mid;
            else
                r = mid - 1;
        }
        rad[i] = l;
        cerr << l;
    }

    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        solve(i, l, r);
    }
    set<int> st;
    for (int i = 0; i <= n; i++) {
        for (auto j : ask1[i]) {
            int mid = (ql[j] + qr[j]) >> 1;
            auto it = st.lower_bound(mid);
            if (it != st.begin()) {
                --it;
                ans[j] =max(it-l+1,lcp[j])
            }
        }
    }
    return 0;
}
