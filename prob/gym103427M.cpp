#include <bits/stdc++.h>
using namespace std;
const int MXN = 3e6 + 5, LG = 31 - __builtin_clz(MXN);
int n;
char str[MXN];
namespace SA {
typedef int arrn[MXN];
arrn sa, rk, tmp, ork, cnt;
int h[LG + 1][MXN];
inline bool cmp(int x, int y, int w) { return ork[x] == ork[y] && ork[x + w] == ork[y + w]; }
inline void init(int n, int m, char *arr) {
    for (int i = 1; i <= m; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cnt[rk[i] = arr[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i--) sa[cnt[rk[i]]--] = i;
    for (int w = 1; w <= n; w <<= 1) {
        int ind = 0;
        for (int i = n - w + 1; i <= n; i++) tmp[++ind] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) tmp[++ind] = sa[i] - w;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i], ork[i] = rk[i];
        m = 0;
        for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? m : ++m;
        if (m == n) break;
    }
    arr[n + 1] = -1;
    for (int i = 1, lcp = 0; i <= n; i++) {
        lcp -= !!lcp;
        while (arr[i + lcp] == arr[sa[rk[i] - 1] + lcp]) ++lcp;
        h[0][rk[i]] = lcp;
    }
    for (int i = 1; i <= LG; i++)
        for (int w = 1 << (i - 1), j = n - (1 << i) + 1; j > 0; j--) h[i][j] = min(h[i - 1][j], h[i - 1][j + w]);
}

inline int lcp(int x, int y) {
    x = rk[x], y = rk[y];
    if (x > y) swap(x, y);
    ++x;
    int lg = 31 - __builtin_clz(y - x + 1);
    return min(h[lg][x], h[lg][y - (1 << lg) + 1]);
}
} // namespace SA

using ll = long long;
struct data {
    ll from, tol;
} q[MXN];

// str[x..r]<str[y..r]
bool cmp(ll x, ll y, ll r) {
    ll lcp = SA::lcp(x, y);
    /* cerr<<lcp; */
    if (x + lcp <= r && y + lcp <= r) return str[x + lcp] < str[y + lcp];
    return x > y;
}
ll ql = 1, qr;
int main() {
    /* freopen("test.in", "r", stdin); */
    /* freopen("test..out","w",stdout); */
    cin >> (str + 1);
    n = strlen(str + 1);
    SA::init(n, 200, str);

    /* cmp(2, 18, 18); */
    q[++qr]={1,1};
    for(ll i=2;i<=n;i++){
        while(qr>=ql && q[qr].tol>=i &&  cmp(q[qr].from,i,q[qr].tol))--qr;
        int l=max(q[qr].tol,i),r=n;
        while(l<r){
            ll mid=(l+r)>>1;
            if(cmp(q[qr].from,i,mid))r=mid;
            else l=mid+1;
        }
        if(cmp(q[qr].from,i,l))q[++qr]={i,l};
    }
    q[qr+1].tol=n+1;
    for(ll i=ql;i<=qr;i++){
        for(int j=q[i].tol;j<q[i+1].tol;j++)
            cout<<q[i].from<<" "<<j<<'\n';
    }

    return 0;
}
