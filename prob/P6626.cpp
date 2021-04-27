#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

typedef pair<int,int> pi;
const int MXN=1e5+5;
int n,m;
vector<int> e[MXN];
vector<pi> q[MXN];

bool vis[MXN];
int sz[MXN],cnt[MXN],ans[MXN];


void calsz(int p,int fa){
	sz[p]=1;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		calsz(nx,p);
		sz[p]+=sz[nx];
	}
}
int calrt(int p,int fa,int tot){
	bool f=tot<=(sz[p]<<1);
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		int tmp=calrt(nx,p,tot);
		if(~tmp)return tmp;
		f&=tot>=(sz[nx]<<1);
	}
	return f?p:-1;
}
void dfsmod(int p,int fa,int dpth,int k){
	cnt[dpth]+=k;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		dfsmod(nx,p,dpth+1,k);
	}
}
void dfsque(int p,int fa,int dpth){
	for(size_t i=0;i<q[p].size();i++){
		pi tmp=q[p][i];
		if(tmp.fi>=dpth)ans[tmp.se]+=cnt[tmp.fi-dpth];
	}
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx] || nx==fa)continue;
		dfsque(nx,p,dpth+1);
	}
}


void dfz(int p){
	calsz(p,0);
	p=calrt(p,0,sz[p]);
	vis[p]=1;
	cnt[0]++;
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx])continue;
		dfsmod(nx,0,1,1);
	}
	for(size_t i=0;i<q[p].size();i++){
		pi tmp=q[p][i];
		ans[tmp.se]+=cnt[tmp.fi];
	}
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx])continue;
		dfsmod(nx,0,1,-1);
		dfsque(nx,0,1);
		dfsmod(nx,0,1,1);
	}
	dfsmod(p,0,0,-1);
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		if(vis[nx])continue;
		dfz(nx);
	}
}
int main(){
	int t;
	qio>>t;
	while(t--){
		qio>>n>>m;
		for(int i=1;i<n;i++){
			int ts,tt;
			qio>>ts>>tt;
			e[ts].pb(tt);
			e[tt].pb(ts);
		}
		for(int i=1;i<=m;i++){
			int x,k;
			qio>>x>>k;
			q[x].pb(mp(k,i));
		}
		dfz(1);
		for(int i=1;i<=m;i++)
			qio<<ans[i]<<'\n';
		for(int i=1;i<=n;i++)
			ans[i]=vis[i]=0,e[i].clear(),q[i].clear();
	}

	return 0;
}

