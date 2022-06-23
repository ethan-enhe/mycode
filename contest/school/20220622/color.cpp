#include<bits/stdc++.h>
#define fi first
#define se second
#define BI(x) (((x)+B-1)/B)
#define BS(x) (((x)-1)*B+1)
#define BE(x) min(n,(x)*B)
using namespace std;
using ll=long long;
const char nl='\n';
const ll B=400,MXN=1e5+5,BC=260,P=998244353;
int cnt[BC][MXN],_cnt[MXN];
ll ans[BC][BC];
ll n,m,arr[MXN],inv[MXN];
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
ll solve(ll l,ll r){
	ll li=BI(l),ri=BI(r),res=1;
	if(li==ri){
		for(ll i=l;i<=r;i++){
			ll cc=++_cnt[arr[i]];
			res=res*inv[cc]%P*(cc+1)%P;
		}
		for(ll i=l;i<=r;i++)
			_cnt[arr[i]]=0;
	}
	else{
		res=ans[li+1][ri-1];
		for(ll i=l;i<=BE(li);i++)_cnt[arr[i]]=cnt[ri-1][arr[i]]-cnt[li][arr[i]];
		for(ll i=BS(ri);i<=r;i++)_cnt[arr[i]]=cnt[ri-1][arr[i]]-cnt[li][arr[i]];
		for(ll i=l;i<=BE(li);i++){
			ll cc=++_cnt[arr[i]];
			res=res*inv[cc]%P*(cc+1)%P;
		}
		for(ll i=BS(ri);i<=r;i++){
			ll cc=++_cnt[arr[i]];
			res=res*inv[cc]%P*(cc+1)%P;
		}
		for(ll i=l;i<=BE(li);i++)_cnt[arr[i]]=0;
		for(ll i=BS(ri);i<=r;i++)_cnt[arr[i]]=0;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>arr[i];
		inv[i]=qpow(i,P-2);
	}
	for(ll i=1;i<=BI(n);i++){
		memcpy(cnt[i],cnt[i-1],sizeof(cnt[i]));
		for(ll j=BS(i);j<=BE(i);j++)
			++cnt[i][arr[j]];
		ans[i][i-1]=1;
		memset(_cnt,0,sizeof(_cnt));
		for(ll j=i;j<=BI(n);j++){
			ans[i][j]=ans[i][j-1];
			for(ll k=BS(j);k<=BE(j);k++){
				ll cc=++_cnt[arr[k]];
				ans[i][j]=ans[i][j]*inv[cc]%P*(cc+1)%P;
			}
		}
	}
	memset(_cnt,0,sizeof(_cnt));
	cin>>m;
	ll last=0;
	while(m--){
		ll l,r;
		cin>>l>>r;
		l^=last,r^=last;
		cout<<(last=solve(l,r))<<nl;
	}
	return 0;
}
