#include <bits/stdc++.h>
#define ll long long
#define int ll
#define ld long double
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define REP(i, j) for (int i = 0; i < j; ++i)
#define REPA(i, j) for (int i = 1; i <= j; ++i)
#define vi vector<int>
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
using namespace std;
const int INF = 0x3f3f3f3f;
// const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9 + 7;
inline void read(int &x) {
    //	short neg=1;
    x = 0;
    char c = getchar();
    /*while(c<'0'||c>'9'){
        if(c=='-')neg=-1;
        c=getchar();
    }*/
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    //	x*=neg;
}
ll quick_mod(ll A, ll B) { // A^B
    ll ret = 1;
    A %= MOD;
    while (B) {
        if (B & 1) ret = ret * A % MOD;
        B >>= 1;
        A = A * A % MOD;
    }
    return ret;
}
inline void chkmin(ll &x, ll y) { x = min(x, y); }
inline void chkmax(ll &x, ll y) { x = max(x, y); }
inline void add(ll &x, ll y) { x = (x + y) % MOD; }
inline ll rev(ll x) { return quick_mod(x, MOD - 2); }
inline int lowbit(int x) { return x & (-x); }
const int MAXN = 1e5 + 100;
int N;
int A1[MAXN], A2[MAXN];
vi v;
signed main(void) {
    ios::sync_with_stdio(0);
    cin >> N;
    int mn1 = INF;
    REP(i, N) cin >> A1[i], mn1 = min(mn1, A1[i]);
    REP(i, N) cin >> A2[i];
    int cnt = 0, p, mn2 = INF;
    REP(i, N) {
        if (A1[i] == mn1) {
            cnt++;
            p = i;
            v.pb(A2[i]);
            mn2 = min(mn2, A2[i]);
        }
    }
    if (mn2 <= mn1) {
        cout << mn1 << ' ' << mn2 << endl;
        return 0;
    }
    bool flag = 0;
    REPA(i, v.size() - 1) {
        if (v[i] != v[i - 1]) {
            if (v[i] > v[i - 1]) {
                flag = 1;
            }
            break;
        }
    }
    vi v2, _v2;
    for (int i = p + 1; i < N; ++i) {
        if (A1[i] < v[0] || (A1[i] == v[0] && flag)) {
            while (v2.size() && v2.back() > A1[i]) v2.pop_back(), _v2.pop_back();
            v2.pb(A1[i]);
            _v2.pb(A2[i]);
        }
    }
    REP(i, cnt) cout << mn1 << ' ';
    REP(i, v2.size()) cout << v2[i] << ' ';
    REP(i, v.size()) cout << v[i] << ' ';
    REP(i, _v2.size()) cout << _v2[i] << ' ';
    cout << endl;
    return 0;
}
/*
think twice, code once;
think once, debug forever.
*/
