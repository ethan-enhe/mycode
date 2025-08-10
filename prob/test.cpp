#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
const int MOD = 1000000007;

<<<<<<< HEAD
using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
tpl pair<T, T> &operator+=(pair<T, T> &x, const pair<T, T> &y) { return x.fi += y.fi, x.se += y.se, x; }
tpl pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi + y.fi, x.se + y.se}; }
tpl pair<T, T> &operator-=(pair<T, T> &x, const pair<T, T> &y) { return x.fi -= y.fi, x.se -= y.se, x; }
tpl pair<T, T> operator-(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi - y.fi, x.se - y.se}; }
tpl pair<T, T> &operator*=(pair<T, T> &x, const ll &y) { return x.fi *= y, x.se *= y, x; }
tpl pair<T, T> operator*(const pair<T, T> &x, const ll &y) { return {x.fi * y, x.se * y}; }
tpl istream &operator>>(istream &is, pair<T, T> &y) { return is >> y.fi >> y.se; }
tpl ostream &operator<<(ostream &os, const pair<T, T> &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
tpl T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (!a || !b) return a | b;
    ll U = __builtin_ctzll(a), V = __builtin_ctzll(b);
    a >>= U, b >>= V;
    if (U > V) U = V;
    while (a) {
        if (a < b) swap(a, b);
        a -= b;
        a >>= __builtin_ctzll(a);
    }
    return b << U;
}
tpl void umx(T &x, const T &y) { x = max(x, y); }
tpl void umn(T &x, const T &y) { x = min(x, y); }
bool inrng(const ll &x, const ll &l, const ll &r) { return l <= x && x <= r; }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
ll ri(const ll &l, const ll &r) { return uniform_int_distribution<ll>(l, r)(mr); }
ld rd(const ld &l, const ld &r) { return uniform_real_distribution<ld>(l, r)(mr); }
//}}}
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    tpl mod(const T &_v) : v(_v) { assert(_v >= 0 && _v < P); }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
    mod operator+(const mod &y) const { return mod(*this) += y; }
    mod operator-(const mod &y) const { return mod(*this) -= y; }
    mod operator*(const mod &y) const { return mod(*this) *= y; }
    mod operator/(const mod &y) const { return mod(*this) /= y; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y.v = incr(x % P), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e5 + 5;

ll n, m, arr[MXN];

bitset<MXN> reach[MXN];
set<ll> g[MXN], _g[MXN];
bool tp[MXN];
ll w[MXN];
void upd(int p) {
    queue<int> q;
    q.push(p);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        bitset<MXN> nxreach;
        nxreach.reset();
        nxreach[p] = 1;
        for (auto v : g[p]) nxreach |= reach[v];
        if (nxreach != reach[p]) {
            reach[p] = nxreach;
            for (auto v : _g[p]) q.push(v);
        }
    }
}
void ae(int s, int t, int tp = 1) {
    if (tp == 1) {
        g[s].insert(t);
        _g[t].insert(s);
    } else {
        g[s].erase(t);
        _g[t].erase(s);
    }
}
bitset<MXN> dead;
bitset<MXN> msk;
void prt(int x) {
    cerr << x << ": ";
    for (int i = 0; i < MXN; i++)
        if (msk[i] && reach[x][i]) cerr << i << " ";
    cerr << endl;
}

void printedge() {
    cerr << "---" << endl;
    for (int i = 0; i < MXN; i++)
        if (msk[i])
            for (auto &j : g[i]) cerr << i << " " << j << endl;
    cerr << "---" << endl;
}
int main() {
    freopen("test.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MXN; i++) reach[i][i] = 1;
    cin >> m;
    while (m--) {
        string op;
        cin >> op;
        if (op == "AddNode") {
            int id, c, p;
            char x;
            cin >> id;
            msk[id] = 1;
            cin >> x;
            tp[id] = x == 'S';
            cin >> w[id];
            cin >> c;
            while (c--) {
                cin >> p;
                ae(p, id);
                upd(p);
            }
            cin >> c;
            while (c--) {
                cin >> p;
                ae(id, p);
            }
            upd(id);
        }
        if (op == "SetRoot") {
            for (auto v : g[0]) {
                _g[v].erase(0);
            }
            g[0].clear();

            int c;
            cin >> c;
            while (c--) {
                int x;
                cin >> x;
                ae(0, x);
            }
            upd(0);
            // prt(0);
        }
        if (op == "AddEdge") {
            int x, y;
            cin >> x >> y;
            ae(x, y);
            upd(x);
        }
        if (op == "DeleteEdge") {
            int x, y;
            cin >> x >> y;
            ae(x, y, -1);
            upd(x);
        }
        if (op == "Ask") {
            // printedge();
            int x;
            cin >> x;
            bitset<MXN> curdead = msk & (~reach[0]);
            curdead &= ~dead;
            dead |= curdead;
            vector<int> ans;
            while (curdead.any()) {
                int i = curdead._Find_first();
                ans.push_back(i);
                curdead[i] = 0;
            }
            cout << ans.size() << nl;
            for (auto i : ans) cout << i << " ";
            cout << nl;
        }
    }
    return 0;
}
=======
vector<int> mobius;
vector<int> fact;
vector<int> inv_fact;

void compute_mobius(int n) {
    mobius.resize(n + 1, 1);
    for (int p = 2; p <= n; ++p) {
        if (mobius[p] == 1) {
            for (int multiple = p; multiple <= n; multiple += p) {
                mobius[multiple] *= -p;
            }
            for (int multiple = p * p; multiple <= n; multiple += p * p) {
                mobius[multiple] = 0;
            }
        }
        if (mobius[p] == p) {
            mobius[p] = 1;
        } else if (mobius[p] == -p) {
            mobius[p] = -1;
        } else {
            int tmp = mobius[p];
            bool square = false;
            unordered_map<int, int> factor;
            while (tmp != 1) {
                int div = mobius[tmp];
                if (factor[div]) {
                    square = true;
                    break;
                }
                factor[div] = 1;
                tmp /= div;
            }
            mobius[p] = square ? 0 : pow(-1, factor.size());
        }
    }
}
int pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * 1LL * a % mod;
        }
        a = a * 1LL * a % mod;
        b >>= 1;
    }
    return res;
}

void compute_factorials(int n, int mod) {
    fact.resize(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * 1LL * i % mod;
    }
    inv_fact.resize(n + 1, 1);
    inv_fact[n] = pow(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * 1LL * (i + 1) % mod;
    }
}

vector<int> get_divisors(int x) {
    vector<int> divs;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            divs.push_back(i);
            if (i != x / i) divs.push_back(x / i);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    compute_mobius(3000000);
    compute_factorials(3000000, MOD);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c, k;
        cin >> a >> b >> c >> k;
        vector<int> d(k);
        for (int i = 0; i < k; ++i) {
            cin >> d[i];
        }
        vector<int> div_a = get_divisors(a);
        vector<int> div_b = get_divisors(b);
        vector<int> div_c = get_divisors(c);
        long long total = 0;
        for (int da : div_a) {
            for (int db : div_b) {
                for (int dc : div_c) {
                    int m_a = a / da;
                    int m_b = b / db;
                    int m_c = c / dc;
                    int m = m_a * m_b * m_c;
                    bool valid = true;
                    for (int di : d) {
                        if (di % m != 0) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;
                    int mu = mobius[m_a] * mobius[m_b] % MOD * mobius[m_c] % MOD;
                    if (mu == 0) continue;
                    int dc_total = da * db % MOD * dc % MOD;
                    dc_total = dc_total % MOD;
                    long long term = fact[dc_total];
                    for (int di : d) {
                        int cnt = di / m;
                        term = term * 1LL * inv_fact[cnt] % MOD;
                    }
                    term = term * 1LL * mu % MOD;
                    total = (total + term) % MOD;
                }
            }
        }
        cout << total << endl;
    }
    return 0;
}
>>>>>>> 1d40f61214deac98f1e86db46f169f347f734980
