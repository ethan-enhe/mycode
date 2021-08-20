#include<bits/stdc++.h>
using namespace std;

//{{{ Def
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dbg(x) cerr<<#x<<"="<<(x)<<endl;
#define inv(x) qpow(x,P-2)

typedef double db;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef vector<ll> vi;
//}}}


//{{{ Const
const char nl='\n';
const db EPS=1e-9;
const ull B=131;
const ll INF=1e18,P=1e9+7;
//}}}



//{{{ Func
il ll qpow(ll x,ll y){
    ll r=1;
    while(y){
        if(y&1)r=r*x%P;
        x=x*x%P,y>>=1;
    }
    return r;
}
il ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
il ll mod(ll x){
	if(x>=P)return x-P;
	if(x<0)return x+P;
	return x;
}
il void add(ll &x,ll y){x=mod(x+y);}
template<class T>il void cmx(T &x,T y){x=max(x,y);}
template<class T>il void cmn(T &x,T y){x=min(x,y);}
//}}}


const ll MXN=5e5+5;
ll n,m,k;
ll arr[MXN];

il void solve(){

}


int main(){
	//freopen(".in","r",stdin),freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	//cin>>t;while(t--)
	solve();

	return 0;
}