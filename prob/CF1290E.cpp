#include <bits/stdc++.h>

using namespace std;

//{{{ FastIO
namespace fio{
const int BS=1<<20;
char ibuf[BS],*ip1=ibuf,*ip2=ibuf;
char obuf[BS],*op=obuf;
#define gc() (ip1==ip2 && (ip2=(ip1=ibuf)+fread(ibuf,1,BS,stdin),ip1==ip2)?EOF:*ip1++)
#define flsh() (fwrite(obuf,1,op-obuf,stdout),op=obuf)
#define pc(x) (*op++=(x),op==obuf+BS && flsh())
struct flusher{inline ~flusher(){flsh();}}tmp;

template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),!isdigit(c))if(c=='-')f=1;
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}
inline void read(char &x){while(x=gc(),isspace(x));}
inline void read(char *x){
	while(*x=gc(),isspace(*x))if(*x==EOF)return;
	while(*++x=gc(),!isspace(*x) && *x!=EOF);
	*x=0;
}
template<class T>
inline void prt(T x){
	if(x<0)pc('-'),x=-x;
	if(x>9)prt(x/10);
	pc(x%10^48);
}
inline void prt(const char x){pc(x);}
inline void prt(char *x){while(*x)pc(*x++);}
inline void prt(const char x[]){for(int i=0;x[i];i++)pc(x[i]);}
#undef gc
#undef pc
#undef flsh
}

void prt(){}
template <typename T1, typename... T2>
void prt(const T1 x,const T2... y) {
	fio::prt(x);
	prt(y...);
}
void read(){}
template <typename T1, typename... T2>
void read(T1 &x, T2 &...y) {
	fio::read(x);
	read(y...);
}
//}}}
//{{{ Def
#define fi first
#define se second
#define pb push_back
#define log(fmt...) fprintf(stderr, fmt)
#define va2d(x, y) x[(y.fi)][(y.se)]

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll, ll> pi;
mt19937_64 myrand(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
template <class T>
T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
template <class T>
void umx(T &x, T y) {
    x = max(x, y);
}
template <class T>
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
const ll INF = 1e18;
const ll MXN = 1.5e5+5;
ll n, m;
ll arr[MXN];

struct segt{
	static const int NR=MXN<<2;
#define ls p<<1
#define rs p<<1|1
	struct tag{
		//最大，个数，标记
		ll v,c,t;
	}f[NR],s[NR];//最大值信息，除了最大值的信息
	//和
	ll sum[NR];
#define add(x) x[p].v+=x##d,x[p].t+=x##d
	void addt(ll p,ll fd,ll sd,bool notf){
		if(notf)fd=sd;
		add(f),add(s);
		sum[p]=f[p].c*f[p].v+s[p].c*s[p].v;
	}
	void pushd(ll p){
		addt(ls,f[p].t,s[p].t,f[ls].v!=f[p].v);
		addt(rs,f[p].t,s[p].t,f[rs].v!=f[p].v);
		f[p].t=s[p].t=0;
	}
	void pushu(ll p){
		sum[p]=sum[ls]+sum[rs];
		if(f[ls].v>f[rs].v){
			f[p].v=f[ls].v,f[p].c=f[ls].c;
			s[p].v=max(s[ls].v,f[rs].v);
			s[p].c=s[ls].c+f[rs].c+s[rs].c;
		}
	}
}pre,suf;


int main() {
#ifndef ONLINE_JUDGE
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    // ll t;scanf("%lld",&t);while(t--)
	read(n);
	for(int i=1;i<=n;i++){
		ll tmp;
		read(tmp);
		arr[tmp]=i;
	}

    return 0;
}

