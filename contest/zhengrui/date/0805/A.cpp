#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e3+5;
vector<ll> l[MXN];
ll n,m,k;
ll f1[MXN][MXN],f2[MXN][MXN];
//long long !!!!;
int main(){
	//freopen("test.in","r",stdin);
	scanf("%lld%lld%lld",&n,&m,&k);
	while(k--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		l[x].push_back(y);
	}
	for(ll i=1;i<=m;i++)
		for(ll j=i+1;j<=m;j++){
			ll cnt=0;
			for(ll k=1;k<=n;k++){
				bool f=0;
				for(ll x:l[k])
					if(x>=i && x<=j){
						f=1;
						if(x==j || x==i)cnt=0;
					}
				if(!f){
					f1[k][j]+=cnt;
					cnt++;
				}
			}
			cnt=0;
			for(ll k=n;k;k--){
				bool f=0;
				for(ll x:l[k])
					if(x>=i && x<=j){
						f=1;
						if(x==j || x==i)cnt=0;
					}
				if(!f){
					f2[k][i]+=cnt;
					cnt++;
				}
			}
		}
	ll ans=0;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			ans+=f1[i][j]*f2[i][j];
	cout<<ans;
	return 0;
}
