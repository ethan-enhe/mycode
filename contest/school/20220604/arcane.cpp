#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MXN=2e5+5,P=998244353;
char str[MXN],tmp[MXN];
ll n,q;
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
ll solve(ll l,ll r){
	ll s=0,cnt=0;
	for(ll i=l;i<=r;i++){
		ll va=0;
		for(ll j=i;j<=r;j++){
			va=(va*10+str[j]-'0')%P;
			s=(s+va)%P;
			++cnt;
		}
	}
	return s*qpow(cnt,P-2)%P;
}
void mdf(ll l,ll r,ll x){
	for(ll i=r;i<=r+x;i++)
		tmp[i-r]=str[i];
	for(ll i=l;i<=l+x;i++)
		str[i]=tmp[i-l];
}
int main(){
	freopen("arcane.in","r",stdin);
	freopen("arcane.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	cin>>(str+1);
	while(q--){
		ll a,b,c,d;
		cin>>a>>b>>c;
		if(a==1)
			cout<<solve(b,c)<<'\n';
		else{
			cin>>d;
			mdf(b,c,d);
		}
	}
	return 0;
}

