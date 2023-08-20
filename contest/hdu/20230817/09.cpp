#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;
const ll P = 1e9 + 7;
const char nl = '\n';
const ll INF = 1e18;
const ll FAR = 1.5e9;
const ll MXN = 5e5 + 5;
const ll far = 1e9;

ll n, m,d0;
map<ll, ll> delt;
void hill(ll l, ll r) {
    ll mid = (l + r) >> 1;

    delt[mid] += -(mid - l + 1) + r - mid - 1;
    delt[mid + 1] += mid - l - (r - mid - 1 + 1);
}
void modf(const vector<ll> &coor) {
    ll x=coor.front();
    d0 += x-1;
    delt[1] -= x ;
    for (ll i = 1; i < coor.size(); i++) hill(coor[i - 1], coor[i]);
    // for (ll i = 0; i < coor.size(); i++) delt[coor[i]]+=2;
}
vector<ll> x[MXN];
int main() {
    // ios::sync_with_stdio(0);
    // qio.tie(0);
    ll t;
    qio >> t;
    while (t--) {
        delt.clear();
        d0=0;
        qio >> n >> m;
        for (ll i = 1; i <= n; i++) {
            ll tmp;
            qio >> tmp;
            ll c;
            qio >> c;
            delt[tmp]+=c*2;
            while (c--) {
                ll y;
                qio >> y;
                x[y].push_back(tmp);
            }
        }
        for (ll i = 1; i <= m; i++) {
            sort(all(x[i]));
            modf(x[i]);
            x[i].clear();
        }
        /*
        ll s = 0, d = d0, last = 0;
        ll ans = INF;
        for (auto &i : delt) {
            s += d * (i.fi - last);
            if (i.fi >= 1 && i.fi <= far) {
                ans = min(ans, s);
            }
            d += i.se;
            last = i.fi;
        }
        cout << ans << nl;
        */
    }
    return 0;
}
