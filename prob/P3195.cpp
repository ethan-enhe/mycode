#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;
//dp[j]+(f[i]-f[j]-l)^2
//dp[j]+f[j]^2+2f[j]L+L^2+f[i]^2-2f[i]L-2f[i]f[j]
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pi;
const ll INF=1e18;
const ll MXN=5e4+5;
ll n,l;
ll ql=1,qr,f[MXN],dp[MXN];
pi q[MXN];
inline ld inter(pi x,pi y){
	if(x.fi==y.fi)return x.se>y.se?-INF:INF;
	return ld(x.se-y.se)/(y.fi-x.fi);
}
inline ll cal(pi f,ll x){return x*f.fi+f.se;}
int main(){
	freopen("test.in","r",stdin);
	scanf("%lld%lld",&n,&l);
	l++;
	q[++qr]=mp(0,0);
	for(ll i=1;i<=n;i++){
		scanf("%lld",f+i);
		f[i]+=1+f[i-1];
		while(ql<qr && inter(q[ql],q[ql+1])<=f[i])ql++;
		dp[i]=cal(q[ql],f[i])+l*l+f[i]*f[i]-2*f[i]*l;
		pi tmp=mp(-2*f[i],dp[i]+f[i]*f[i]+2*f[i]*l);
		while(ql<qr && inter(q[qr-1],q[qr])>inter(q[qr],tmp))qr--;
		q[++qr]=tmp;
	}
	printf("%lld",dp[n]);
	return 0;
}
