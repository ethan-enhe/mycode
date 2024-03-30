#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pi=pair<int,int>;
const ll INF=1e9;
const ll P=1e9+7;
vector<pi> delt;
ll qpow(ll x,ll y){
        ll r=1;
        y=(y+P-1)%(P-1);
        while(y){
                if(y&1)r=r*x%P;
                x=x*x%P,y>>=1;
        }
        return r;
}
int main(){
        ios::sync_with_stdio(0);
        cin.tie(0);
        ll n,m,s,t;
        cin>>n>>m>>s>>t;
        for(ll i=1;i<=m;i++){
                ll x,l,r;
                cin>>x>>l>>r;
				delt.push_back({l,-1});
				delt.push_back({r,1});
        }
		delt.push_back({s,0});
		delt.push_back({t+1,0});
		sort(delt.begin(),delt.end());
        ll last=s,sum=n;
        ll ans=1;
        for(auto [u,v]:delt){
                ans=ans*qpow(sum,u-last)%P;
                sum+=v;
                last=u;
        }
        cout<<ans<<endl;
        return 0;
}
