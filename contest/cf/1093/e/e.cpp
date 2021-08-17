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


const ll MXN=1e6+5;

ll n,m,k;
ll p[MXN],brr[MXN];
ll top,qcnt,s[MXN],ans[MXN];
inline void mod(ll x,ll y){for(;x<=n;x+=x&(-x))s[x]+=y;}
inline ll que(ll x){ll res=0;for(;x;x^=x&(-x))res+=s[x];return res;}
inline ll sum(ll x,ll y){return que(y)-que(x-1);}

struct op{ll tp,x,ylow,yup;}arr[MXN],tmp[MXN];
inline bool cmp(op x,op y){return x.x<y.x;}
inline void cdq(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1,lind=l;
	cdq(l,mid),cdq(mid+1,r);
	for(ll i=mid+1;i<=r;i++){
		if(!arr[i].tp)continue;
		for(;lind<=mid && arr[lind].x<=arr[i].x;lind++)
			if(!arr[lind].tp)mod(arr[lind].ylow,arr[lind].yup);
		if(arr[i].tp>0)ans[arr[i].tp]+=sum(arr[i].ylow,arr[i].yup);
		else ans[-arr[i].tp]-=sum(arr[i].ylow,arr[i].yup);
	}
	while(--lind>=l)
		if(!arr[lind].tp)
			mod(arr[lind].ylow,-arr[lind].yup);
	inplace_merge(arr+l,arr+mid+1,arr+r+1,cmp);
}
inline void solve(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1,tmp;i<=n;i++){
		scanf("%lld",&tmp);
		p[tmp]=i;
	}
	for(ll i=1,tmp;i<=n;i++){
		scanf("%lld",&tmp);
		brr[i]=p[tmp];
		arr[++top]={0,i,brr[i],1};
	}
	ll tp,a,b,c,d;
	while(m--){
		scanf("%lld%lld%lld",&tp,&a,&b);
		if(tp==1){
			scanf("%lld%lld",&c,&d);
			swap(a,c),swap(b,d);
			++qcnt;
			arr[++top]=op{-qcnt,a-1,b,d};
			arr[++top]=op{qcnt,c,b,d};
		}
		else{
			arr[++top]={0,a,brr[a],-1};
			arr[++top]={0,b,brr[b],-1};
			swap(brr[a],brr[b]);
			arr[++top]={0,a,brr[a],1};
			arr[++top]={0,b,brr[b],1};
		}

	}
	cdq(1,top);
	for(int i=1;i<=qcnt;i++)printf("%lld\n",ans[i]);
    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//ll tq;scanf("%lld",&tq);while(tq--)
	solve();
	return 0;
}
