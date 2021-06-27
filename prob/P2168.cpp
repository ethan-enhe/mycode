#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
priority_queue<pi> q;
ll n,k;
int main(){
	scanf("%lld%lld",&n,&k);
	while(n--){
		ll tmp;
		scanf("%lld",&tmp);
		q.push(mp(-tmp,0));
	}
	while((q.size()-1)%(k-1))
		q.push(mp(0,1e9));
	ll sum=0;
	while(q.size()!=1){
		pi nx;
		for(ll i=0;i!=k;i++){
			pi cur=q.top();
			nx.fi+=cur.fi;
			nx.se=min(nx.se,cur.se);
			q.pop();
		}
		nx.se--;
		sum-=nx.fi;
		q.push(nx);
	}
	printf("%lld\n%lld",sum,-q.top().se);
	return 0;
}
