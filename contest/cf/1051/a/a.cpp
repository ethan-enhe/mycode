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


const ll MXN=105;

ll n,m,k;
bool suf[MXN][3],pre[3];
char str[MXN];
inline int tp(char x){
	if(isdigit(x))return 0;
	if(x>='A' && x<='Z')return 1;
	return 2;
}
inline bool chk(ll len){
	memset(suf,0,sizeof(suf));
	memset(pre,0,sizeof(pre));
	for(int i=n;i;i--){
		for(int j=0;j<3;j++)suf[i][j]=suf[i+1][j];
		suf[i][tp(str[i])]=1;
	}
	for(int i=1;i+len-1<=n;i++){
		ll cnt=3;
		for(int j=0;j<3;j++)
			cnt-=pre[j]|suf[i+len][j];
		if(cnt<=len){
			ll ind=i;
			for(int j=0;j<3;j++)
				if(!pre[j] && !suf[i+len][j])
					str[ind++]="1Aa"[j];
			return 1;
		}
		pre[tp(str[i])]=1;
	}
	return 0;
}
inline void solve(){
	scanf("%s",str+1);
	n=strlen(str+1);
	if(chk(0))printf("%s\n",str+1);
	else if(chk(1))printf("%s\n",str+1);
	else if(chk(2))printf("%s\n",str+1);
	else if(chk(3))printf("%s\n",str+1);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}
