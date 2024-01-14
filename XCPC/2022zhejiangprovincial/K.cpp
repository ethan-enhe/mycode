#include <bits/stdc++.h>
using namespace std;
const int K = 50;
const int MXK = K * 2 + 5;
const int MXN = 50005;
const int MXMQ = 100005;
bitset<MXK> vis[MXN];
int n, m, q;
struct query {
    int tp, x, y;
} ask[MXMQ];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++) {
        cin >> ask[i].tp >> ask[i].x;
        if (ask[i].tp == 2) cin >> ask[i].y;
    }

    return 0;
}
