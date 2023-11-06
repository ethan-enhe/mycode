#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rd scanf
#define pt printf
#define setp(x) setprecision(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define sz(x) (int)x.size()
#define umn(x,y) x=min(x,y)
#define umx(x,y) x=max(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef queue<ll> qi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

const ll INF=1e18;
const ll P=1e9+7;
const ll MXN=1e5+5;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(const ll &x,const ll &y){return !y?x:gcd(y,x%y);}
inline void pbin(const ll &x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m,k;
ll arr[MXN];
bool can[1005];
bool can2[1005];
inline void solve(){
    int tmp=0,cnt=0;
	mem(can,1);
	mem(can2,0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
        if(can[arr[i]])can[arr[i]]=0;
        else {
			cnt++;
			tmp=arr[i];
        }
	}
    if(cnt>1){
        cout<<0<<endl;
        return;
    }
	for(int i=1;i<=1000;i++)
		for(int j=1;(j<<1)<i;j++)
			can2[i]|=can[i-j]&can[j];
	cnt=0;
	for(int i=1;i<=n;i++){
        if(!tmp)cnt+=can2[arr[i]];
        else if(arr[i]==tmp)cnt+=can2[arr[i]];
	}
	cout<<cnt<<endl;


    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	cin>>tq;
	while(tq--)solve();
	return 0;
}

