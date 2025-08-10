#include <bits/stdc++.h>

using namespace std;
const char nl = '\n';
const int INF = 1e9;
const int MXN = 3e5 + 5;
const int LG = 20;
const int NR = 1 << LG;

int n, m, arr[MXN];
struct trie {
#define ls p << 1
#define rs p << 1 | 1
    int t[NR * 4 + 5];
    void mdf(int p, int dig, int i, int v) {
        if (dig == -1) {
            t[p] = v;
            return;
        }
        if ((i >> dig) & 1)
            mdf(rs, dig - 1, i, v);
        else
            mdf(ls, dig - 1, i, v);
        t[p] = max(t[ls], t[rs]);
    }
    int getmx(int p, int dig, int i, int rng) {
        if (dig == -1) return 0;
        bool f = (i >> dig) & 1;
        int s_f = f ? ls : rs;
        int sf = f ? rs : ls;
        if (t[s_f] >= rng)
            return getmx(s_f, dig - 1, i, rng) ^ (1 << dig);
        else
            return getmx(sf, dig - 1, i, rng);
    }
#undef ls
#undef rs
} mxt, mnt;

stack<int> mxs, mns;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("perfect.in", "r", stdin);
    freopen("perfect.out", "w", stdout);
    int ans = 0;
    cin >> n;
    mxs.push(0);
    mns.push(0);
    for (int i = 1; i <= n; i++) {
        int mxpre, mnpre;
        cin >> arr[i];
        while (mxs.top() && arr[mxs.top()] < arr[i]) {
            mxt.mdf(1, LG - 1, arr[mxs.top()], 0);
            mxs.pop();
        }
        mxpre = mxs.top();
        mxt.mdf(1, LG - 1, arr[i], i);
        mxs.push(i);
        while (mns.top() && arr[mns.top()] > arr[i]) {
            mnt.mdf(1, LG - 1, arr[mns.top()], 0);
            mns.pop();
        }
        mnpre = mns.top();
        mnt.mdf(1, LG - 1, arr[i], i);
        mns.push(i);
        ans = max({ans, mxt.getmx(1, LG - 1, arr[i], mnpre + 1), mnt.getmx(1, LG - 1, arr[i], mxpre + 1)});
        // cout << mxpre << " " << mnpre << " " << ans << nl;
    }
    cout << ans << nl;

    return 0;
}

