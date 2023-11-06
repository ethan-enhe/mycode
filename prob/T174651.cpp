#include<bits/stdc++.h>
#define pb push_back
using namespace std;
namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

const int MXN=2e6+5;
const int MXTP=20;
int n,m,num,arr[MXN],order[MXN];
int win[MXTP],dp[MXN][MXTP];

int head[MXN],nxt[MXN],ter[MXN],edgec;
inline void ae(const int &ts,const int &tt){
	nxt[++edgec]=head[ts];head[ts]=edgec;
	ter[edgec]=tt;
}
void dfs(int p,int fa){
	for(int i=0,tmp=win[arr[p]];i<num;i++,tmp>>=1)
		dp[p][i]=tmp&1?dp[fa][i]:p;
	for(int i=head[p];i;i=nxt[i])dfs(ter[i],p);
}

int main(){
	qio>>n>>m>>num;
	for(int i=0;i<num;i++)
		for(int j=0,tmp;j<num;j++){
			qio>>tmp;
			win[j]|=tmp<<i;
		}

	for(int i=1;i<=n;i++){
		qio>>arr[i];
		arr[i]--;
	}
	for(int i=1,ts,tt;i<n;i++){
		qio>>ts>>tt;
		ae(ts,tt);
	}
	dfs(1,0);
	while(m--){
		int k,targ;
		qio>>k>>targ;
		for(int i=1;i<=k;i++){
			qio>>order[i];
			order[i]--;
		}
		for(;k;k--)targ=dp[targ][order[k]];
		qio<<(int)(!targ)<<'\n';
	}
	return 0;
}
