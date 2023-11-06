#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (31 - __builtin_clz(x))
#define popc(x) __builtin_popcount(x)

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
istream &operator>>(istream &is, pi &y) { return is >> y.fi >> y.se; }
ostream &operator<<(ostream &os, pi &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
template <typename T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <typename T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, T y) {
    x = min(x, y);
}
ll abs(pi x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
bool insqr(pi x, pi lt, pi rb) { return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se; }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
void setp(ll x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void read(T &x, int l, int r) {
    for (int i = l; i <= r; i++) cin >> x[i];
}
template <typename T>
void prt(T &x, int l, int r, char join = ' ') {
    for (int i = l; i <= r; i++) cout << x[i] << join;
}
//}}}
const ll MXN = 1005, LG = 40;

ll task, chance;
ld prec[MXN], precj[MXN];

#define cal(i, j) res.v[i][j] = v[i][0] * b.v[0][j] + v[i][1] * b.v[1][j]
struct mat {
    ld v[2][2];
    mat(bool f = 0) {
        v[0][0] = v[1][1] = f;
        v[1][0] = v[0][1] = 0;
    }
    mat operator*(const mat &b) const {
        mat res;
        cal(0, 0);
        cal(0, 1);
        cal(1, 0);
        cal(1, 1);
        return res;
    }
} init, res, tmp[LG + 1];
void init_mat(ld k, ld b) { tmp[0].v[0][0] = k, tmp[0].v[1][0] = b, tmp[0].v[1][1] = 1; }

int main() {
    freopen("camp.in","r",stdin);
    freopen("camp.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(10);
    cin >> task >> chance;
    --task;

    ld c = qpow((ld)0.5, task);
    for (int j = 0; j <= task; j++) {
        prec[j + 1] = prec[j] + c;
        precj[j + 1] = precj[j] + c * (1 + j);
        c = c * (task - j) / (j + 1);
    }

    init.v[0][1] = 1;
    ll ind = 0;
    while (ind < chance) {
        ll mid = (ll)init.v[0][0] - 1;
        init_mat(prec[mid + 1], precj[task + 1] - precj[mid + 1]);
        for (ll i = 1; ind + (1ll << i) < chance; i++) tmp[i] = tmp[i - 1] * tmp[i - 1];
        for (ll i = LG; ~i; i--)
            if (ind + (1ll << i) < chance) {
                res = init * tmp[i];
                if ((ll)res.v[0][0] - 1 == mid) {
                    ind += (1ll << i);
                    init = res;
                }
            }
        ++ind;
        init = init * tmp[0];
    }
    cout << init.v[0][0] << endl;

    return 0;
}
