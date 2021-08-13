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
const ll P=998244353;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}
inline void add(ll &x,ll y){
	x=(x+y)%P;
}


const ll MXD=25;
ll n,m,lim;
char l[MXD],r[MXD];
ll cnt[MXD][1<<10][2][2],sum[MXD][1<<10][2][2];
inline ll cal(char *str,bool eq=0){
	ll len=strlen(str+1);
	memset(cnt,0,sizeof(cnt));
	memset(sum,0,sizeof(sum));
	cnt[0][0][1][1]=1;
	for(ll i=0;i<len;i++)
		for(ll j=0;j!=1024;j++){
			if(__builtin_popcount(j)>lim)continue;
			for(ll k=0;k<=9;k++){
				ll upp=str[i+1]-'0',nj=j|(1<<k),vk=k*qpow(10,len-i-1);
				add(cnt[i+1][nj][0][0],cnt[i][j][0][0]);
				add(cnt[i+1][k==0?0:nj][0][k==0],cnt[i][j][0][1]);
				add(sum[i+1][nj][0][0],sum[i][j][0][0]+cnt[i][j][0][0]*vk);
				add(sum[i+1][k==0?0:nj][0][k==0],sum[i][j][0][1]+cnt[i][j][0][1]*vk);
				if(k<=upp){
					add(cnt[i+1][nj][k==upp][0],cnt[i][j][1][0]);
					add(cnt[i+1][k==0?0:nj][k==upp][k==0],cnt[i][j][1][1]);
					add(sum[i+1][nj][k==upp][0],sum[i][j][1][0]+cnt[i][j][1][0]*vk);
					add(sum[i+1][k==0?0:nj][k==upp][k==0],sum[i][j][1][1]+cnt[i][j][1][1]*vk);
				}
			}
		}
	ll ans=0;
	for(ll i=0;i!=1024;i++)
		if(__builtin_popcount(i)<=lim){
			add(ans,sum[len][i][0][0]+sum[len][i][0][1]);
			if(eq)add(ans,sum[len][i][1][0]+sum[len][i][1][1]);
		}
	return ans;
}
inline void solve(){
	scanf("%s %s%lld",l+1,r+1,&lim);
	//cout<<cal(r,1);
	printf("%lld",(cal(r,1)-cal(l)+P)%P);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}
