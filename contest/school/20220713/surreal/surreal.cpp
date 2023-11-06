#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using lll=__int128;
using pi=pair<ll,ll>;
const ll INF=1e18,P=998244353,INV2=499122177;
const char nl='\n';
ll n,q,ans;
set<pi> hull;
ll len(pi x,pi y){return (x.se+y.se)%P*(y.fi-x.fi+1)%P*INV2%P;}
void ers(set<pi>::iterator it){
	//cerr<<it->fi<<endl;
	auto pre=it,suf=it;
	--pre;++suf;
	ans=(ans-len(*pre,*it)-len(*it,*suf)+len(*pre,*suf)+it->se)%P;
	hull.erase(it);
}
void ins(pi x){
	auto suf=hull.lower_bound(x),pre=suf;
	--pre;
	ans=(ans-len(*pre,*suf)+len(*pre,x)+len(x,*suf)-x.se)%P;
	hull.insert(x);
}
bool ishull(pi x,pi y,pi z){
	return lll(y.se-x.se)*lll(z.fi-y.fi)>lll(z.se-y.se)*lll(y.fi-x.fi);
}
void mdf(pi x){
	auto it=hull.lower_bound({x.fi,-INF});
	if(it->fi==x.fi){
		ers(it);
		it=hull.lower_bound({x.fi,-INF});
	}
	while(1){
		auto nx=it;++nx;
		if(nx==hull.end() || ishull(x,*it,*nx))break;
		ers(it);
		it=hull.lower_bound({x.fi,-INF});
	}
	it=--hull.lower_bound({x.fi,-INF});
	while(1){
		if(it==hull.begin())break;
		auto nx=it;--nx;
		if(ishull(*nx,*it,x))break;
		ers(it);
		it=--hull.lower_bound({x.fi,-INF});
	}
	it=hull.lower_bound({x.fi,-INF});
	auto pre=it;--pre;
	if(ishull(*pre,x,*it))ins(x);
}


int main(){
	freopen("surreal.in","r",stdin);
	freopen("surreal.out","w",stdout);
	assert(2*INV2%P==1);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	hull.insert({0,0});
	hull.insert({n+1,0});
	for(ll i=1,x;i<=n;i++){
		cin>>x;
		mdf({i,x});
	}
	cout<<(ans+P)%P<<nl;
	while(q--){
		ll x,y;
		cin>>x>>y;
		mdf({x,y});
		cout<<(ans+P)%P<<nl;
	}
	return 0;
}

