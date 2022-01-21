#include <algorithm>
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXN=20;
ll n,q;
pi arr[MXN];
ll pool[MXN],pc;
ll fa[MXN];
inline void find(ll x){

}
int main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&arr[i].fi,&arr[i].se);
		arr[i].se++;
		pool[++pc]=arr[i].fi;
		pool[++pc]=arr[i].se;
	}
	sort(pool+1,pool+1+pc);
	pc=unique(pool+1,pool+1+pc)-pool-1;

	for(int i=1;i<=q;i++){

	}
	return 0;
}
