/* #pragma GCC optimize("Ofast","-funroll-loops") */
/* #pragma GCC target("sse4.1","sse4.2","ssse3","sse3","sse2","sse","avx2","avx","popcnt","tune=native") */
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define log2(x) (63 - __builtin_clzll(x))
#define popc(x) __builtin_popcountll(x)
#define all(x) (x).begin(), (x).end()
#define unq(x) x.erase(unique(all(x)), x.end())
#define gen generate

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
//}}}
//{{{ Func
template <typename T1, typename T2>
pair<T1, T2> operator+(const pair<T1, T2> &x, const pair<T1, T2> &y) {
    return {x.fi + y.fi, x.se + y.se};
}
template <typename T1, typename T2>
pair<T1, T2> operator-(const pair<T1, T2> &x, const pair<T1, T2> &y) {
    return {x.fi - y.fi, x.se - y.se};
}
template <typename T1, typename T2>
pair<T1, T2> operator*(const pair<T1, T2> &x, const ll &y) {
    return {x.fi * y, x.se * y};
}
template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &y) {
    return is >> y.fi >> y.se;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &y) {
    return os << '(' << y.fi << ',' << y.se << ')';
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
void umx(T &x, const T &y) {
    x = max(x, y);
}
template <typename T>
void umn(T &x, const T &y) {
    x = min(x, y);
}
ll abs(const pi &x) { return (x.fi < 0 ? -x.fi : x.fi) + (x.se < 0 ? -x.se : x.se); }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
ll ri(const ll &l, const ll &r) {
    uniform_int_distribution<ll> res(l, r);
    return res(mr);
}
ld rd(const ld &l, const ld &r) {
    uniform_real_distribution<ld> res(l, r);
    return res(mr);
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T>
void prt(T &x, const ll &l, const ll &r, const char &join = ' ') {
    for (ll i = l; i <= r; i++) cout << x[i] << join;
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
//}}}
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() : v() {}
    template <typename T>
    mod(const T &_v) : v(_v) {
        if (v >= P || v < 0) v = incr(v % P);
    }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod operator+(const mod &y) const { return mod{redu(v + y.v)}; }
    mod operator-(const mod &y) const { return mod{incr(v - y.v)}; }
    mod operator*(const mod &y) const { return mod{1ll * v * y.v % P}; }
    mod operator/(const mod &y) const { return mod{1ll * v * (ll)qpow(y, P - 2) % P}; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = 1ll * v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = 1ll * v * (ll)qpow(y, P - 2) % P, *this; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y = mod(x), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const ll INF = 1e18;
const pi go[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char nl = '\n';
const ll MXN = 1e6 + 5;

ll n, m;
struct p{
    ll x,y,z;
}arr[MXN];
ll py[MXN],pyi;
ll pz[MXN],pzi;
bool cmp(const p &x,const p &y){
    return x.x<y.x;
}
ll smn[MXN],pmx[MXN];
void updmx(ll x,ll y){
    for(ll i=x;i<=n;i+=i&(-i))
        umx(pmx[i],y);
}
void updmn(ll x,ll y){
    for(ll i=x;i;i-=i&(-i))
        umn(smn[i],y);
}
ll gmx(ll x){
    ll r=0;
    for(;x;x-=x&(-x))
        umx(r,pmx[x]);
    return r;
}
ll gmn (ll x){
    ll r=INF;
    for(;x<=n;x+=x&(-x))
        umn(r,smn[x]);
    return r;
}

struct que{
    ll x,y,v,tp;
}q[MXN];
ll qid;

void addp(pi x){
    q[++qid]={x.fi,x.se,py[x.fi]+pz[x.se],0};
}
void ins(ll id){
    ll mxz=gmx(arr[id].y-1);
    if(mxz>arr[id].z){
        addp({arr[id].y,mxz});
    }
    ll l=arr[id].y,r=n;
    while(l<r){
        ll mid=(l+r+1)>>1;
        if(gmn(mid)<arr[id].z)l=mid;
        else r=mid-1;
    }
    if(l!=arr[id].y)
        addp({l,arr[id].z});
    updmx(arr[id].y,arr[id].z);
    updmn(arr[id].y,arr[id].z);
}
ll ans=-1;
bool cmpx(const que &x,const que &y){return x.x>y.x;}
namespace _cdq{
void updmx(ll x,ll y){
    for(ll i=x;i;i-=i&(-i))
        umx(pmx[i],y);
}
ll gmx(ll x){
    ll r=-INF;
    for(;x<=n;x+=x&(-x))
        umx(r,pmx[x]);
    return r;
}
void clr(ll x){
    for(ll i=x;i;i-=i&(-i))
        pmx[i]=-INF;
}
void cdq(ll l,ll r){
    if(l==r)return;
    ll mid=(l+r)>>1,ind=l;
    cdq(l,mid),cdq(mid+1,r);
    for(ll i=mid+1;i<=r;i++){
        while(ind<=mid && q[ind].x>q[i].x){
            if(q[ind].tp==0){
                updmx(q[ind].y,q[ind].v);
                if(l==1 && r==7 && q[ind].y==3){
                }
            }
            ++ind;
        }
        if(q[i].tp)
            umx(ans,gmx(q[i].y+1)+q[i].v);
    }
    while(--ind>=l)
        clr(q[ind].y);
    inplace_merge(q+l,q+mid+1,q+r+1,cmpx);
}
}
int main() {
    /* freopen("test.in","r",stdin); */
    /* freopen("test.out","w",stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    memset(smn,0x3f,sizeof(smn));
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].x>>arr[i].y>>arr[i].z;
        py[i]=arr[i].y;
        pz[i]=arr[i].z;
    }
    sort(py+1,py+1+n);
    sort(pz+1,pz+1+n);
    pyi=unique(py+1,py+1+n)-py-1;
    pzi=unique(pz+1,pz+1+n)-pz-1;
    sort(arr+1,arr+1+n,cmp);
    for(int i=1;i<=n;i++){
        arr[i].y=lower_bound(py+1,py+1+pyi,arr[i].y)-py;
        arr[i].z=lower_bound(pz+1,pz+1+pzi,arr[i].z)-pz;
    }
    for(ll i=1,ind=0;i<=n;i++){
        while(ind<n && arr[ind+1].x<arr[i].x)
            ins(++ind);
        q[++qid]={arr[i].y,arr[i].z,arr[i].x,1};
    }
    memset(pmx,~0x3f,sizeof(pmx));
    _cdq::cdq(1,qid);
    cout<<ans;
    return 0;
}


