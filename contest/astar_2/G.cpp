#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
const ll MXN=3005;
const ll MXQ=3e5+5;

ll n,m,q;
ll ans[MXQ];
pi ask[MXQ];
ll mxa[MXN],mxb[MXN],mxc[MXN],mxab[MXN];

void dp(ll *x,ll w,ll v){
	for(ll i=m;i>=w;i--){
		x[i]=max(x[i],x[i-w]+v);
	}
}
stack<pi> area;
ll calc(ll cost_c,ll d){
	return max(0ll,mxab[m-cost_c]*(100-d+mxc[cost_c]));
}
int main(){
	//freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>q;
	for(ll i=1;i<=n;i++){
		ll c,t,w;
		cin>>c>>t>>w;
		if(t==1)dp(mxa,c,w);
		else if(t==2)dp(mxb,c,w);
		else if(t==3)dp(mxc,c,w);
	}
	for(ll i=0;i<=m;i++)
		for(ll j=0;i+j<=m;j++)
			mxab[i+j]=max(mxab[i+j],((ll)100+mxa[i])*(100+mxb[j]));
	for(ll i=1;i<=q;i++){
		ll d;
		cin>>d;
		ask[i]={d,i};
	}
	sort(ask+1,ask+1+q);


	area.push({0,1});
	for(ll i=1;i<=m;i++){
		while(!area.empty() && calc(i,ask[area.top().se].fi)>=calc(area.top().fi,ask[area.top().se].fi))area.pop();
		if(area.empty()){
			area.push({i,1});
		}
		else{
			ll l=area.top().se,r=q+1;
			while(l<r){
				ll mid=(l+r)>>1;
				if(calc(i,ask[mid].fi)>=calc(area.top().fi,ask[mid].fi))r=mid;
				else l=mid+1;
			}
			if(l<=q)area.push({i,l});
		}
	}
	//cerr<<calc(4,1)<<" "<<calc(10,1)<<endl;

	/*
	while(!area.empty()){
		cerr<<area.top().fi<<" "<<area.top().se<<endl;
		area.pop();
	}
	*/

	for(ll i=q;i;i--){
		while(area.top().se>i)area.pop();
		ans[ask[i].se]=calc(area.top().fi,ask[i].fi);
	}
	for(ll i=1;i<=q;i++)
		cout<<ans[i]<<"\n";
	return 0;
}




