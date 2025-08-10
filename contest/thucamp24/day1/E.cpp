#include <bits/stdc++.h>
using namespace std;
using ll = int;
const ll MXN = 1e6 + 5;
const ll LG = 20;
ll tp, n;
ll arr[MXN];
ll rnd[MXN];

ll sum[MXN];
void add(ll x, ll v) {
    for (; x <= n; x += x & -x) {
        sum[x] += v;
    }
}
ll pre(ll x) {
    ll ret = 0;
    for (; x; x -= x & -x) {
        ret += sum[x];
    }
    return ret;
}

ll sub[MXN], subidx;
ll getord() {
    ll cnt = 0;
    for (int i = 1; i <= subidx; i++) {
        ll x = sub[i];
        cnt += pre(x);
        add(x, 1);
    }
    for (int i = 1; i <= subidx; i++) {
        ll x = sub[i];
        add(x, -1);
    }
    return cnt;
}
ll getsum() {
    ll sum = 0;
    for (int i = 1; i <= subidx; i++) sum += sub[i];
    return sum;
}
void gen_subarr(ll bit) {
    subidx = 0;
    for (ll i = 1; i <= n; i++)
        if (((i >> bit) & 1) == 0) sub[++subidx] = arr[i];
}
char str[MXN];
ll idx;

ll read(ll bits) {
    ll res = 0;
    while (bits--) {
        res <<= 1;
        res += str[++idx] - '0';
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(65536);
    cin >> tp >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        // arr[i] = i;
        rnd[i] = rand();
    }
    if (tp == 1) {
        for (ll i = 0; i < LG; i++) {
            gen_subarr(i);
            ll cnt = getord();
            ll sum = getsum(); // sum of sub
            cout << (cnt & 1) << bitset<9>(sum);
        }
        cout << endl;
    } else {
        cin >> (str + 1);

        ll idx1 = 0, idx2 = 0;
        ll delt = -1;
        for (ll i = 0; i < LG; i++) {
            gen_subarr(i);
            ll cnt = getord() & 1;
            ll sum = getsum() & 511; // sum of sub
            ll stdcnt = read(1);
            ll stdsum = read(9);
            if (stdsum == sum) { // 这位相同
                if (cnt == stdcnt) {
                    idx1 |= (1 << i);
                    idx2 |= (1 << i);
                }
            } else {
                ll tmp = (stdsum - sum) & 511;
                if (delt == -1) {
                    delt = tmp;
                    idx1 |= (1 << i);
                } else {
                    if (delt == tmp) {
                        idx1 |= (1 << i);
                    } else {
                        idx2 |= (1 << i);
                    }
                }
            }
        }
        // cout << idx1 << ' ' << idx2;
        swap(arr[idx1], arr[idx2]);
        for (ll i = 1; i <= n; i++) cout << arr[i] << ' ';
        cout << endl;
    }

    return 0;
}
