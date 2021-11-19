#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef pair<int, int> pi;
const int MXN = 1e6 + 6;
int t, n, arr[MXN], mxi[MXN], mni[MXN];
bool dead[MXN];
set<pi> q;
inline void solve() {
    q.clear();
    for (int i = 1; i <= n; i++) {
        q.insert({arr[i], i});
        dead[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        auto p = --q.end();
        pi mx = *p;
        mxi[i] = p->second;
        q.erase(p);

        p = q.begin();
        mx.first -= p->first;
        mni[i] = p->second;
        q.erase(p);
        q.insert(mx);
    }
    int ind = n - 1;
    for (int i = n - 1; i; i--) {
        dead[mni[i]] = 1;
        if (dead[mxi[i]])
            while (ind >= i) dead[mni[ind--]] = 0;
    }
    printf("%d\n", n - ind);
}
int main() {
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
    scanf("%d%d", &t, &n);
    for (int i = 1; i <= n; i++) scanf("%d", arr + i);
    solve();
    while (--t) {
        int k;
        scanf("%d", &k);
        while (k--) {
            int i, x;
            scanf("%d%d", &i, &x);
            arr[i] = x;
        }
        solve();
    }
    return 0;
}
