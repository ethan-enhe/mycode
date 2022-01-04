#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
using namespace std;
//{{{ FastIO
namespace fio {
const int BS = 1 << 20;
char ibuf[BS], *ip1 = ibuf, *ip2 = ibuf;
char obuf[BS], *op = obuf;
#define gc() (ip1 == ip2 && (ip2 = (ip1 = ibuf) + fread(ibuf, 1, BS, stdin), ip1 == ip2) ? EOF : *ip1++)
#define flsh() (fwrite(obuf, 1, op - obuf, stdout), op = obuf)
#define pc(x) (*op++ = (x), op == obuf + BS && flsh())
struct flusher {
    inline ~flusher() { flsh(); }
} tmp;

template <typename T>
inline void read(T &x) {
    bool f = 0;
    x = 0;
    char c;
    while (c = gc(), !isdigit(c))
        if (c == '-') f = 1;
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    if (f) x = -x;
}
inline void read(char &x) {
    while (x = gc(), isspace(x))
        ;
}
inline void read(char *x) {
    while (*x = gc(), isspace(*x))
        if (*x == EOF) return;
    while (*++x = gc(), !isspace(*x) && *x != EOF)
        ;
    *x = 0;
}
template <typename T>
inline void prt(T x) {
    if (x < 0) pc('-'), x = -x;
    if (x > 9) prt(x / 10);
    pc(x % 10 ^ 48);
}
inline void prt(const char x) { pc(x); }
inline void prt(char *x) {
    while (*x) pc(*x++);
}
inline void prt(const char x[]) {
    for (int i = 0; x[i]; i++) pc(x[i]);
}
#undef gc
#undef pc
#undef flsh
} // namespace fio

void prt() {}
template <typename T1, typename... T2>
void prt(const T1 x, const T2... y) {
    fio::prt(x);
    prt(y...);
}
void read() {}
template <typename T1, typename... T2>
void read(T1 &x, T2 &... y) {
    fio::read(x);
    read(y...);
}
//}}}
//{{{ Def
#define fi first
#define se second
#define pb push_back

#ifdef ONLINE_JUDGE
#define log(fmt...) void()
#else
#define log(fmt...) fprintf(stderr, fmt)
#endif

#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
const ll INF = 1e18;
const ll P = 1e9 + 7;
const ll MXN = 1e6 + 5;
const ld EPS=1e-9;
//{{{ Func
ll redu(const ll &x) {
    if (x < P) return x;
    if (x < (P << 1)) return x - P;
    return x % P;
}
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
ll abs(pi x) { return abs(x.fi) + abs(x.se); }
ll randint(ll l, ll r) {
    uniform_int_distribution<ll> res(l, r);
    return res(myrand);
}
ld randdb(ld l, ld r) {
    uniform_real_distribution<ld> res(l, r);
    return res(myrand);
}
//}}}
//{{{ Type
const pi go[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
pi operator+(const pi &x, const pi &y) { return pi(x.fi + y.fi, x.se + y.se); }
pi operator-(const pi &x, const pi &y) { return pi(x.fi - y.fi, x.se - y.se); }
pi operator*(const pi &x, const ll &y) { return pi(x.fi * y, x.se * y); }
struct mll {
    ll v;
    explicit mll(ll _v = 0) : v(_v) {}
    explicit operator ll() const { return v; }
    mll operator+(const mll &y) const { return mll(redu(v + y.v)); }
    mll operator-(const mll &y) const { return mll(redu(P + v - y.v)); }
    mll operator*(const mll &y) const { return mll(redu(v * y.v)); }
    mll operator/(const mll &y) const { return mll(redu(v * (ll)qpow(y, P - 2))); }
    mll &operator=(const mll &y) { return v = y.v, *this; }
    mll &operator+=(const mll &y) { return v = redu(v + y.v), *this; }
    mll &operator-=(const mll &y) { return v = redu(P + v - y.v), *this; }
    mll &operator*=(const mll &y) { return v = redu(v * y.v), *this; }
    mll &operator/=(const mll &y) { return v = redu(v * (ll)qpow(y, P - 2)), *this; }
    bool operator==(const mll &y) const { return v == y.v; }
    bool operator!=(const mll &y) const { return v != y.v; }
};
mll ltm(const ll &x) { return mll(redu(x % P + P)); }
template <typename T>
struct myvec {
    T *v;
    int sz, dsz;
    myvec() { v = NULL, sz = dsz = 0; }
    ~myvec() { free(v); }
    operator T *() const { return v; }
    T *begin() { return v; }
    T *end() { return v + sz; }
    void rsz(int x) { v = (T *)realloc(v, sizeof(T) * (dsz = sz = x)); }
    void pb(T x) {
        if (sz == dsz) v = (T *)realloc(v, sizeof(T) * (dsz = dsz << 1 | 1));
        v[sz++] = x;
    }
    void fill(T x) {
        for (int i = 0; i < sz; i++) v[i] = x;
    }
};
//}}}
ll n, m;
ll tea[MXN],suf[MXN][3];
pair<ld,ll> gro[MXN];
vector<ll> stu[MXN];
int main(int argc, char *argv[]) {
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ll t;
	read(t);
	while(t--){
		read(n,m);
		for(int i=1;i<=n;i++)
			read(tea[i]);
		for(int i=1;i<=m;i++){
			ll k,b;
			read(k);
			stu[i].clear();
			for(int j=1;j<=k;j++){
				read(b);
				stu[i].push_back(b);
				gro[i].fi+=b;
			}
			gro[i].fi/=k,gro[i].se=i;
		}
		sort(tea+1,tea+1+n);
		sort(gro+1,gro+1+m);
		// for(int i=1;i<=n;i++)
		// 	cout<<tea[i]<<" ";
		// cout<<endl;
		// for(int i=1;i<=m;i++)
		// 	cout<<gro[i].fi<<" ";
		// cout<<endl;
		ll ind=n;
		for(int i=0;i<3;i++)
			suf[m+1][i]=m+1;
		for(int i=m;i;i--){
			while(ind && tea[ind]-EPS>=gro[i].fi)ind--;
			cerr<<ind<<endl;
			for(int j=0;j<3;j++){
				if((n-ind)>=(m-i+j))suf[i][j]=suf[i+1][j];
				else suf[i][j]=i;
				cerr<<suf[i][j]<<" ";
			}
			cerr<<endl;
		}
		cerr<<endl;
		for(int i=1;i<=m;i++){
			ll curg=gro[i].se;
			for(ll &j:stu[curg]){
				ld tmp=stu[curg].size()==1?-INF:(gro[i].fi*stu[curg].size()-j)/(stu[curg].size()-1);
				ll ind=upper_bound(gro+1,gro+1+m,pair<ld,ll>{tmp,-INF})-gro;
				ll indt=lower_bound(tea+1,tea+1+n,ceil(tmp))-tea;
				bool f=(n-indt+1)>=(m-ind+2-(ind<=i));
				if(j==37)cerr<<tmp<<" "<<indt<<" "<<ind<<endl;
				if(ind>i){
					f&=suf[ind][1]==m+1;
					f&=suf[i+1][2]>=ind;
					f&=suf[1][1]>=i;
				}
				else{
					f&=suf[i+1][1]==m+1;
					f&=suf[ind][1]>=i;
					f&=suf[1][1]>=ind;
				}
				j=f;
				// cerr<<ind<<" ";
				// cerr<<tmp<<endl;
			}
		}
		for(int i=1;i<=m;i++)
			for(ll j:stu[i])
				prt(j);
		prt('\n');
	}

    return 0;
}
