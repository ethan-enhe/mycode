#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

struct mod;

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const int INF = 1e9;
const int BIG = 1e7;
struct edge {
    int u, v, w;
};
vec<edge> ans;

int n;
void ae(int u, int v, int w) {
    assert(u <= n && v <= n && u >= 1 && v >= 1);
    assert(abs(w) <= INF);
    ans.push_back({u, v, w});
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    /* freopen("gen.in","r",stdin); */
    /* freopen("gen.out", "w", stdout); */
    n = 60;
    for (int i = 1, w = INF - BIG; i < n / 2; i++) {
        ae(i, i + 1, 1);
        ae(i, i + n / 2, BIG - n * i);
        ae(i + n / 2, i + 1, -(BIG - n * i) - w);
        w >>= 1;
    }
    assert(n <= 60 && ans.size() <= 100);

    cout << n << " " << ans.size() << endl;
    for (edge &i : ans) cout << i.u << " " << i.v << " " << i.w << endl;
    return 0;
}
