#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//ll
const ll MXN=1e6+5;
ll n,cnt[MXN];
vector<ll> e[MXN],rt,allcnt[MXN];

inline void dfs(ll p,ll dpth){
	cnt[dpth]++;
	for(ll nx:e[p])
		dfs(nx,dpth+1);
}
int main(){
	scanf("%lld",&n);
	for(ll i=1,fa;i<=n;i++){
		scanf("%lld",&fa);
		(fa?e[fa]:rt).push_back(i);
	}
	for(ll i:rt){
		dfs(i,1);
		for(ll j=1;cnt[j];j++){
			allcnt[j].push_back(cnt[j]);
			cnt[j]=0;
		}
	}
	ll res=0;
	for(ll i=1;!allcnt[i].empty();i++){
		ll sum=0,sum_sq=0,sum_cu=0;
		for(ll j:allcnt[i]){
			sum+=j;
			sum_sq+=j*j;
			sum_cu+=j*j*j;
		}
		res+=(sum*sum*sum-3*sum_sq*sum+2*sum_cu)/6;
	}
	printf("%lld",res);

	return 0;
}
