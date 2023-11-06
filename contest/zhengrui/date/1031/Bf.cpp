#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=20;
ll n,q,ans;
pi arr[MXN];
ll s[MXN];
inline void dfs(ll id){
	if(id==n+1){
		bool f=1;
		for(int i=1;i<=q;i++){
			ll tmp=0;
			for(int j=arr[i].fi;j<=arr[i].se;j++)
				tmp=(tmp*10+s[j])%9;
			if(tmp){
				f=0;
				break;
			}
		}
		ans+=f;
		return;
	}
	for(int i=0;i<=9;i++){
		s[id]=i;
		dfs(id+1);
	}

}

int main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=q;i++)
		scanf("%lld%lld",&arr[i].fi,&arr[i].se);
	dfs(1);
	printf("%lld",ans);
	return 0;
}
