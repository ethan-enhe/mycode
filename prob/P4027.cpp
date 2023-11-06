#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<double,double> pr;
const ll MXN=1e5+5;
const ll INF=1e18;
ll n;
double arr[MXN],brr[MXN],rate[MXN],dp[MXN],pool[MXN];


struct node{ll ls,rs;pr line;}t[MXN<<2];ll rt,nodec;
inline double f(pr line,ll x){return line.fi*pool[x]+line.se;}
inline double f(pr line,double x){return line.fi*x+line.se;}
inline ll nnode(){return t[++nodec].line=mp(0,-INF),nodec;}
inline void mod(ll &p,ll l,ll r,pr ml){
	ll mid=(l+r)>>1;
	if(!p)p=nnode();
	if(f(ml,mid)>f(t[p].line,mid))swap(ml,t[p].line);
	if(l==r)return;
	ml.fi<t[p].line.fi?mod(t[p].ls,l,mid,ml):mod(t[p].rs,mid+1,r,ml);
}
inline double que(ll p,ll l,ll r,double qx){
	if(!p || l==r)return f(t[p].line,qx);
	ll mid=(l+r)>>1;
	return max(f(t[p].line,qx),qx>pool[mid]?que(t[p].rs,mid+1,r,qx):que(t[p].ls,l,mid,qx));
}
int main(){
	scanf("%lld%lf",&n,&dp[0]);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",arr+i,brr+i,rate+i);
		pool[i]=brr[i]/arr[i];
	}
	sort(pool+1,pool+1+n);
	for(int i=1;i<=n;i++){
		dp[i]=max(dp[i-1],arr[i]*que(rt,1,n,brr[i]/arr[i]));
		double k=dp[i]/(arr[i]*rate[i]+brr[i]);
		mod(rt,1,n,mp(k,k*rate[i]));
	}
	printf("%.3f",dp[n]);
	
	return 0;
}
