#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rd scanf
#define pt printf
#define setp(x) setprecision(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define sz(x) (int)x.size()
#define umn(x,y) x=min(x,y)
#define umx(x,y) x=max(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef queue<ll> qi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

const ll INF=1e18;
const ll P=1e9+7;
const ll MXN=505;
const ll NXG[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

inline ll mod(ll x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,m;
char vis[MXN][MXN];
pi fa[MXN][MXN];
pi find(pi tmp){
	ll x=tmp.fi,y=tmp.se;
	if(fa[x][y]==tmp)return tmp;
	return fa[x][y]=find(fa[x][y]);
}
inline void merge(pi x,pi y){
	x=find(x),y=find(y);
	fa[y.fi][y.se]=x;
}

queue<pi> q;
inline void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>(vis[i]+1);
		for(int j=1;j<=m;j++){
			fa[i][j]=mp(i,j);
			if(vis[i][j]=='X')q.push(mp(i,j));
		}
	}
	while(!q.empty()){
		pi p=q.front();
		q.pop();
		vpi np,nfa;bool f=1;
		for(int i=0;i<4;i++){
			pi nx=mp(p.fi+NXG[i][0],p.se+NXG[i][1]);
			if(nx.fi<1 || nx.se<1 || nx.fi>n || nx.se>m)continue;
			if(vis[nx.fi][nx.se]=='.')np.pb(nx);
			else{
				pi tmp=find(nx);
				for(int j=0;j<sz(nfa);j++)
					if(nfa[j]==tmp){
						f=0;
						break;
					}
				nfa.pb(tmp);
			}
		}
		if(f){
			for(int j=0;j<sz(nfa);j++)
				merge(p,nfa[j]);
			vis[p.fi][p.se]='X';
			for(int j=0;j<sz(np);j++)
				q.push(np[j]);
		}
	}
	for(int i=1;i<=n;i++)
		cout<<(vis[i]+1)<<endl;

    
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout<<setiosflags(ios::fixed);
	srand(time(NULL));

	ll tq=1;
	cin>>tq;
	while(tq--)solve();
	return 0;
}
