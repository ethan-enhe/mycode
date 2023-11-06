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

const ll MXN=1005,go[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
ll n,m;
pi arr[MXN];
bool status[MXN],bel[MXN][MXN];
ll eatt[MXN],mat[MXN][MXN];
il bool notvalid(pi p){return p.fi<0 || p.se<0 || p.fi>=MXN || p.se>=MXN;}
struct DSU{
	ll has[MXN][MXN];
	pi fa[MXN][MXN];
	il pi find(pi p){
		if(fa[p.fi][p.se]==p)return p;
		return fa[p.fi][p.se]=find(fa[p.fi][p.se]);
	}
	il void init(){
		for(int i=0;i<MXN;i++)
			for(int j=0;j<MXN;j++)
				fa[i][j]=pi(i,j);
		for(int i=0;i<MXN;i++)
			for(int j=0;j<MXN;j++)
				if(!has[i][j])
					merge(pi(i,j));
	}
	il void merge(pi p){
		for(int i=0;i<4;i++){
			pi nx=pi(p.fi+go[i][0],p.se+go[i][1]);
			if(notvalid(nx))continue;
			if(has[nx.fi][nx.se])continue;
			pi rp=find(p);
			fa[rp.fi][rp.se]=find(nx);
		}
	}
}board[2];
il bool notsur(ll x){return board[~x&1].find(arr[x])==board[~x&1].find(pi(0,0));}

il void solve(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>arr[i].fi>>arr[i].se;
		board[i&1].has[arr[i].fi][arr[i].se]++;
		eatt[i]=INF;
	}
	board[0].init();
	board[1].init();
	for(int i=0;i<n;i++){
		if(notsur(i)){
			status[i]=1;
			eatt[i]=INF;
		}
		//cerr<<status[i];
	}
	//cerr<<nl;
	for(int i=n-1;~i;i--)
		if(--board[i&1].has[arr[i].fi][arr[i].se]==0){
			board[i&1].merge(arr[i]);
			for(int j=~i&1;j<n;j+=2)
				if(!status[j] && notsur(j)){
					eatt[j]=i;
					status[j]=1;
				}
		}
	for(int i=0;i<n;i++)cerr<<(eatt[i]==INF?-1:eatt[i])<<" ";
	cerr<<nl;

	memset(mat,-1,sizeof(mat));
	for(int i=0;i<n;i++){
		if(mat[arr[i].fi][arr[i].se]>=i){
			cout<<"illegal";
			return;
		}
		mat[arr[i].fi][arr[i].se]=eatt[i];
		bel[arr[i].fi][arr[i].se]=i&1;
		/*
		if(eatt[i]<=i){
			bool f=0;
			for(int j=~i&1;j<n;j+=2)
				if(eatt[j]==i){
					f=1;
					break;
				}
			if(!f){
				cout<<"illegal";
				return;
			}
		}
		*/
		for(int j=0;j<8;j+=2){
			ll cnt=-1;
			pi cur=arr[i];
			do{
				cur.fi+=go[j][0];
				cur.se+=go[j][1];
			//if(i==2 && j==4)cerr<<cur.fi<<" "<<cur.se<<endl;
				cnt++;
			}while(!notvalid(cur) && mat[cur.fi][cur.se]>=i && bel[cur.fi][cur.se]==(i&1) && cnt<m);
			cur=arr[i];
			do{
				cur.fi+=go[j+1][0];
				cur.se+=go[j+1][1];
			//if(i==2 && j==4)cerr<<cur.fi<<" "<<cur.se<<endl;
				cnt++;
			}while(!notvalid(cur) && mat[cur.fi][cur.se]>=i && bel[cur.fi][cur.se]==(i&1) && cnt<m);
			if(cnt>=m){
				cout<<(i&1?"Bob ":"Alice ")<<i+1;
				return;
			}
		}
	}
	cout<<"draw";
	
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	//freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

	//ll t;cin>>t;while(t--)
	solve();

	return 0;
}

