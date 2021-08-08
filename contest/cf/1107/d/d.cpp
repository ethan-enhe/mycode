#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18;
const ll P=1e9+7;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=5205;

ll n,m;
char tmp[MXN];
ll mat[MXN][MXN];
inline ll sum(ll x,ll y,ll a){return mat[x+a-1][y+a-1]-mat[x-1][y+a-1]-mat[x+a-1][y-1]+mat[x-1][y-1];}
inline void solve(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%s",tmp+1);
		for(ll j=1;(j<<2)<=n;j++){
			ll v;
			if(tmp[j]>='0' && tmp[j]<='9')v=tmp[j]-'0';
			else v=tmp[j]-'A'+10;
			for(ll k=j<<2;k>(j-1)<<2;k--){
				mat[i][k]=v&1;
				v>>=1;
			}
		}
	}
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			mat[i][j]+=mat[i-1][j]+mat[i][j-1]-mat[i-1][j-1];
	for(ll i=n;i;i--)
		if(n%i==0){
			ll stdsz=i*i;bool f=1;
			for(ll x=1;x<=n;x+=i){
				for(ll y=1;y<=n;y+=i){
					ll tmp=sum(x,y,i);
					if(tmp && tmp!=stdsz){
						f=0;
						break;
					}
				}
				if(!f)break;
			}
			if(f){
				printf("%lld",i);
				return;
			}
		}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}
