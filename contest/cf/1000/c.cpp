#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1e6+5;
typedef ll arrn[MXN];
ll n;
arrn pool,l,r,cov,ans;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld",l+i,r+i);
		pool[i]=l[i],pool[i+n]=r[i]+1;
	}
	sort(pool+1,pool+1+(n<<1));
	for(ll i=1;i<=n;i++){
		cov[lower_bound(pool+1,pool+1+(n<<1),l[i])-pool]++;
		cov[lower_bound(pool+1,pool+1+(n<<1),r[i]+1)-pool]--;
	}
	for(ll i=1;i<=(n<<1);i++){
		cov[i]+=cov[i-1];
		ans[cov[i]]+=pool[i+1]-pool[i];
	}
	for(ll i=1;i<=n;i++)printf("%lld ",ans[i]);
	return 0;
}
