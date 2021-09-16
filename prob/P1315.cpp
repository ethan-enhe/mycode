#include<bits/stdc++.h>
using namespace std;

//{{{ Def
#define il inline
#define fi first
#define se second
#define pb push_back
#define dbg(x) cerr<<#x<<"="<<(x)<<endl;
#define inv(x) qpow(x,P-2)

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<ll,ll> pi;
typedef vector<ll> vi;
//}}}
const char nl='\n';
const ld EPS=1e-9;
const ull B=131;
const ll INF=1e18;
ll P=1e9+7;
//{{{ Func
//{{{ Math
il ll qpow(ll x,ll y){
    ll r=1;
    while(y){
        if(y&1)r=r*x%P;
        x=x*x%P,y>>=1;
    }
    return r;
}
il ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
il ll mod(ll x){
	if(abs(x)>=(P<<1))return x%P;
	if(x>=P)return x-P;
	if(x<=-P)return x+P;
	return x;
}
il void madd(ll &x,ll y){x=mod(x+y);}
il void add(ll &x,ll y){x=x+y;}
il void umx(ll &x,ll y){x=max(x,y);}
il void umn(ll &x,ll y){x=min(x,y);}
il bool cle(ll x,ll y){return x<=y;}
il bool cl(ll x,ll y){return x<y;}
il bool cge(ll x,ll y){return x>=y;}
il bool cg(ll x,ll y){return x>y;}
//}}}
//{{{ Other
il void renum(ll *v,ll sz){
	static ll *pool=NULL;
	pool=(ll*)realloc(pool,sizeof(ll)*(sz+1));
	memcpy(pool,v,sizeof(ll)*(sz+1));
	sort(pool+1,pool+1+sz);
	for(ll i=1;i<=sz;i++)
		v[i]=lower_bound(pool+1,pool+1+sz,v[i])-pool;
}
//}}}
//}}}
//{{{ Algo
//{{{ COMB
namespace comb{
	ll *fac,*ifac;
	il void init(ll sz){
		fac=(ll*)realloc(fac,sizeof(ll)*(sz+1));
		ifac=(ll*)realloc(ifac,sizeof(ll)*(sz+1));
		fac[0]=1;
		for(ll i=1;i<=sz;i++)fac[i]=fac[i-1]*i%P;
		ifac[sz]=inv(fac[sz]);
		for(ll i=sz;i;i--)ifac[i-1]=ifac[i]*i%P;
	}
	il ll c(ll x,ll y){
		if(y>x || y<0)return 0;
		return fac[x]*ifac[y]%P*ifac[x-y]%P;
	}
}
//}}}
//{{{ BIT
template<void (*f)(ll&,ll),const ll DEF_V=0>
struct tarr{
	ll *v,sz;
	il tarr(){v=NULL,sz=0;}
	il ~tarr(){free(v);}
	il void set(ll x=DEF_V){fill(v,v+sz+1,x);}
	il void rsz(ll x){v=(ll*)realloc(v,sizeof(ll)*((sz=x)+1));}
	il void mod(ll x,ll y){for(;x<=sz;x+=x&(-x))f(v[x],y);}
	il ll pre(ll x){ll r=DEF_V;for(;x;x^=x&(-x))f(r,v[x]);return r;}
	il ll lb(ll x,bool (*chk)(ll,ll)=cle){
		ll r=0,cur=DEF_V;
		for(ll i=1<<(ll)log2(sz);i;i>>=1)
			if(r+i<=sz){
				ll nx=cur;f(nx,v[r+i]);
				if(!chk(x,nx)){
					r+=i;
					cur=nx;
				}
			}
		return r+1;
	}
};
//}}}
//}}}

const ll MXN=1e3+5,LG=10;
ll n,m,k,ans;
ll dis[MXN],arr[MXN],mnt[MXN],act[MXN];
ll mni[LG+1][MXN];


struct seg{
	ll l,r,acc;
	il ll cal()const{return arr[r]-arr[l];}
	il bool operator < (const seg &b)const{return cal()<b.cal();}
};
il ll mini(ll x,ll y){return act[y]<act[x]?y:x;}
il ll que(ll l,ll r){
	ll lg=log2(r-l+1);
	return mini(mni[lg][l],mni[lg][r-(1<<lg)+1]);
}
priority_queue<seg> q;

il void split(seg x){
	if(x.r==x.l+1){
		if(x.acc<dis[x.l])q.push(x);
		return;
	}
	ll mid=que(x.l+1,x.r-1);
	if(act[mid]<=x.acc){
		if((mid==x.l+1 && x.acc<dis[x.l]) || mid>x.l+1)q.push({x.l,mid,x.acc});
		split({mid,x.r,x.acc});
	}
	else q.push({x.l,mid,x.acc});
}


il void solve(){
	cin>>n>>m>>k;
	for(ll i=1;i<n;i++)
		cin>>dis[i];
	while(m--){
		ll x,y,z;
		cin>>x>>y>>z;
		ans-=x;
		umx(mnt[y],x);
		arr[z]++;
	}
	for(ll i=2;i<=n;i++){
		umx(mnt[i],mnt[i-1]);
		act[i]=max(act[i-1],mnt[i-1])+dis[i-1];
		ans+=act[i]*arr[i];
		arr[i]+=arr[i-1];
	}
	for(ll i=n;i;i--){
		act[i]-=mnt[i];
		mni[0][i]=i;
		for(ll j=1;i+(1<<j)<=n+1;j++)
			mni[j][i]=mini(mni[j-1][i],mni[j-1][i+(1<<(j-1))]);
	}
	ll last=1;
	for(ll i=2;i<=n;i++)
		if(act[i]<=0){
			q.push({last,i,0});
			last=i;
		}
	if(last!=n)
		q.push({last,n,0});
	while(!q.empty() && k--){
		seg p=q.top();q.pop();
		ans-=p.cal();
		p.acc++;
		split(p);
	}
	cout<<ans;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("test.in","r",stdin);
	//freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

	//ll t;cin>>t;while(t--)
	solve();

	return 0;
}

