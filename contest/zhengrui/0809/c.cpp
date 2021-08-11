#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=2e3+5;
ll n,arr[MXN],ans;
struct pool{
	bool app[MXN];ll cnt;
	inline void clr(){memset(app,cnt=0,sizeof(app));}
	inline bool ins(ll x){
		if(!app[x]){
			cnt++;
			return app[x]=1;
		}
		return 0;
	}
}a,b,c;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld",arr+i);
	for(ll i=1;i<=n;i++){
		a.clr();
		b.clr();
		c.clr();
		ll il=i+1,ir=i+1;
		for(ll j=i;j;j--){
			a.ins(arr[j]);
			while(il<=n && b.cnt<a.cnt)
				b.ins(arr[il++]);
			while(ir<=n && a.app[arr[ir]])
				c.ins(arr[ir++]);
			if(b.cnt==a.cnt)ans+=max(ir-il+1,0ll);
			//cout<<j<<" "<<i<<" "<<il-1<<" "<<ir-1<<" "<<max(ir-il+1,0ll)<<endl;
		}
	}
	printf("%lld",ans);
	return 0;
}
