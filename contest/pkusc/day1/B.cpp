#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
using db=long double;
const char nl='\n';

const ll MXN=5005;
ll n;
pi s[MXN],t[MXN];
db dis[MXN];
bool in(pi x,pi y){
	return x.fi<=y.fi && x.se<=y.se;
}
pair<db,db> itsc(pi x,ll i){
	return {db((t[i].fi-x.fi)*s[i].se+(x.fi-s[i].fi)*t[i].se)/(t[i].fi-s[i].fi),
			db((t[i].se-x.se)*s[i].fi+(x.se-s[i].se)*t[i].fi)/(t[i].se-s[i].se)};
}

db cal(pi x){
	db r=0;
	for(ll i=1;i<=n;i++){
		auto res=itsc(x,i);
		if(in(s[i],x) && in(t[i],x))r+=dis[i];
		else if(in(s[i],x))
			r+=dis[i]*(x.fi-s[i].fi)/(t[i].fi-s[i].fi);
		else if(in(t[i],x))
			r+=dis[i]*(x.se-t[i].se)/(s[i].se-t[i].se);
		else if(res.fi<=x.se)
			r+=dis[i]*((db)x.fi-res.se)/(t[i].fi-s[i].fi);
	}
	return r+1e-10;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>s[i].fi>>s[i].se;
		cin>>t[i].fi>>t[i].se;
		dis[i]=sqrtl((s[i].fi-t[i].fi)*(s[i].fi-t[i].fi)+(s[i].se-t[i].se)*(s[i].se-t[i].se));
	}
	ll q;
	cin>>q;

	while(q--){
		pi qc;
		cin>>qc.fi>>qc.se;
		cout<<fixed<<setprecision(18)<<cal(qc)<<nl;
	}

	return 0;
}

