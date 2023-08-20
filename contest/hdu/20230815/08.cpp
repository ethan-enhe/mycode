// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <stack>
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

using ll = __int128;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

ll n, m, arr[MXN], sum;
int main() {
    int x;
    ll t;
    qio >> x;
    t = x;
    while (t--) {
        ll n;
        qio >> x;
        n = x;
        sum = 0;
        for (ll i = 1; i <= n; i++) {
            qio >> x;
            arr[i] = x;
            sum += arr[i];
        }
        ll ans = 0;
        for (ll i = 1; i <= n; i++) ans += arr[i] * (sum - arr[i]);
        ans /= 2;
        stack<int> res;
        while (ans) {
            res.push(ans % 10);
            ans /= 10;
        }
        while (!res.empty()) {
            cout << res.top();
            res.pop();
        }
        cout << nl;
    }

    return 0;
}
