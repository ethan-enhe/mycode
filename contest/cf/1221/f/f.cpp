#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;

const ll INF=1e18;
const ll P=1e9+7;

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}


const ll MXN=5e5+5,MXCOOR=1e9+5,SZ=1e7;

typedef ll arrSZ[SZ];

ll nodec,rt;
pi mx[SZ];
arrSZ tag,ls,rs;
inline void pushu(ll p){mx[p]=max(mx[ls[p]],mx[rs[p]]);}
inline void addt(ll p,ll mv){mx[p].fi+=mv;}
inline void pushd(ll p){
	addt(ls[p],tag[p]);
	addt(rs[p],tag[p]);
	tag[p]=0;
}
inline void mod(ll &p,ll l,ll r,ll ml,ll mr,ll mv){
	if(!p)p=++nodec;
	if(ml<=l && r<=mr){
		addt(p,mv);
		if(l==r)mx[p].se=l;
		return;
	}
	pushd(p);ll mid=(l+r)>>1;
	if(ml<=mid)mod(ls[p],l,mid,ml,mr,mv);
	if(mr>mid)mod(rs[p],mid+1,r,ml,mr,mv);
	pushu(p);
}
inline pi que(ll p,ll l,ll r,ll ql,ll qr){
	if(!p || (ql<=l && r<=qr))return mx[p];
	pushd(p);pi res={-INF,-1};ll mid=(l+r)>>1;
	if(ql<=mid)res=que(ls[p],l,mid,ql,qr);
	if(qr>mid)res=max(res,que(rs[p],mid+1,r,ql,qr));
	return res;
}


struct p{ll x,y,v;}arr[MXN];
inline bool cmpx(p a,p b){return a.x<b.x;};
inline bool cmpy(p a,p b){return a.y<b.y;};

ll n,m,k;
inline void solve(){
	mx[0].fi=-INF;

	scanf("%lld",&n);
	for(ll i=1,a,b,c;i<=n;i++){
		scanf("%lld%lld%lld",&a,&b,&c);
		if(b>a)swap(a,b);
		arr[i]={a,b,c};
	}
	arr[0].y=arr[n+1].x=-1;
	sort(arr+1,arr+1+n,cmpy);
	for(ll i=1;i<=n;i++)
		if(arr[i].y!=arr[i-1].y)
			mod(rt,0,MXCOOR,arr[i].y,arr[i].y,arr[i].y);
	sort(arr+1,arr+1+n,cmpx);
	ll ans=0,ansl=0,ansr=0;
	for(ll i=1;i<=n;i++){
		//cerr<<arr[i].x<<" mod "<<0<<" "<<arr[i].y<<" "<<arr[i].v<<endl;
		mod(rt,0,MXCOOR,0,arr[i].y,arr[i].v);
		if(arr[i].x!=arr[i+1].x){
			pi tmp=que(rt,0,MXCOOR,0,arr[i].x);
			//cout<<tmp.fi<<" "<<tmp.se<<"!!!\n";
			if(tmp.fi-arr[i].x>=ans){
				ans=tmp.fi-arr[i].x;
				ansl=tmp.se,ansr=arr[i].x;
			}
		}
	}
	printf("%lld\n%lld %lld %lld %lld",ans,ansl,ansl,ansr,ansr);

    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	solve();
	return 0;
}
