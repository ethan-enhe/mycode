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
typedef vector<pi> vpi;
//}}}
const char nl='\n';
const ld EPS=1e-9;
const ull B=131;
const ll INF=1e18;
ll P=1e9+7;
//{{{ Func
//{{{ Math
il pi operator + (const pi &x,const pi &y){return pi(x.fi+y.fi,x.se+y.se);}
il pi operator - (const pi &x,const pi &y){return pi(x.fi-y.fi,x.se-y.se);}
il pi operator * (const pi &x,const ll &y){return pi(x.fi*y,x.se*y);}
il ll qpow(ll x,ll y){
    ll r=1;
    while(y){
        if(y&1)r=r*x%P;
        x=x*x%P,y>>=1;
    }
    return r;
}
il ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
il ll exgcd(ll x,ll y,ll &rx,ll &ry){
	if(!y){
		rx=1,ry=0;
		return x;
	}
	ll g=exgcd(y,x%y,rx,ry);
	swap(rx,ry);
	ry-=rx*(x/y);
	return g;
}
il ll mod(ll x){
	if(abs(x)>=(P<<1))return x%P;
	if(x>=P)return x-P;
	if(x<=-P)return x+P;
	return x;
}
il vpi factor(ll x){
	vpi r;
	for(ll i=2;i*i<=x;i++)
		if(x%i==0){
			pi cur=pi(i,0);
			do x/=i,++cur.se;while(x%i==0);
			r.pb(cur);
		}
	if(x!=1)r.pb(pi(x,1));
	return r;
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
//{{{ SEGT
template<class v_type,class t_type,
	v_type (*merge)(v_type,v_type),void (*addt)(ll,ll,v_type&,t_type&,t_type),
	const v_type DEFAULT_V,const t_type DEFAULT_T,const ll SZ>
struct segt{
#define ls d[p].son[0]
#define rs d[p].son[1]
	struct node{
		v_type v;t_type t;
		ll son[2];
		node(){son[0]=son[1]=0;v=DEFAULT_V,t=DEFAULT_T;}
	}d[SZ];
	ll nodec,root,lb,rb;
	il void init(ll l,ll r){
		nodec=root=0;
		lb=l,rb=r;
		for(int i=0;i<SZ;i++)
			d[i]=node();
	}
	il void pushd(ll p,ll l,ll r){
		if(!ls)ls=++nodec;
		if(!rs)rs=++nodec;
		ll mid=(l+r)>>1;
		addt(l,mid,d[ls].v,d[ls].t,d[p].t);
		addt(mid+1,r,d[rs].v,d[rs].t,d[p].t);
		d[p].t=DEFAULT_T;
	}
	il void _mod(ll &p,ll l,ll r,ll ml,ll mr,t_type mv){
		if(!p)p=++nodec;
		if(ml<=l && r<=mr){
			addt(l,r,d[p].v,d[p].t,mv);
			return;
		}
		ll mid=(l+r)>>1;pushd(p,l,r);
		if(ml<=mid)_mod(ls,l,mid,ml,mr,mv);
		if(mr>mid)_mod(rs,mid+1,r,ml,mr,mv);
		d[p].v=merge(d[ls].v,d[rs].v);
	}
	il void _set(ll &p,ll l,ll r,ll mi,v_type mv){
		if(!p)p=++nodec;
		if(l==r){
			d[p].v=mv;
			return;
		}
		ll mid=(l+r)>>1;pushd(p,l,r);
		if(mi<=mid)_set(ls,l,mid,mi,mv);
		else _set(rs,mid+1,r,mi,mv);
		d[p].v=merge(d[ls].v,d[rs].v);
	}
	il v_type _que(ll p,ll l,ll r,ll ql,ll qr){
		if(!p || (ql<=l && r<=qr))return d[p].v;
		ll mid=(l+r)>>1;v_type res=DEFAULT_V;pushd(p,l,r);
		if(ql<=mid)res=merge(res,_que(ls,l,mid,ql,qr));
		if(qr>mid)res=merge(res,_que(rs,mid+1,r,ql,qr));
		return res;
	}
	il void mod(ll l,ll r,t_type mv){_mod(root,lb,rb,l,r,mv);}
	il void set(ll mi,v_type mv){_set(root,lb,rb,mi,mv);}
	il v_type que(ll l,ll r){return _que(root,lb,rb,l,r);}
};
//}}}
//}}}

const ll MXN=5e5+5;
ll n,m,x;
ll arr[MXN];

il void solve(){
	scanf("%lld%lld",&n,&m);
	if(n>m)
		x=n+m;
	else
		x=(m/n)*n+m%n/2;
	printf("%lld\n",x);
	assert(x%n==m%x);

	
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
#endif
	//ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

	ll t;cin>>t;while(t--)
	solve();

	return 0;
}
