#include<bits/stdc++.h>
using namespace std;

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char buf[1<<20],*p1=buf,*p2=buf;
template<class T>
inline void read(T &x){
	bool f=0;x=0;char c;
	while(c=gc(),c<'0' || c>'9')if(c=='-')f=1;
	while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^48),c=gc();
	if(f)x=-x;
}

#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pi;

const ll MXN=2e5+5;
ll n,x[MXN],c[MXN],s[MXN];
vector<pi> rg[MXN];

int main(){
	read(n);
	for(ll i=1;i<=n;i++)read(x[i]),read(c[i]),read(s[i]);
	for(ll i=1;i<=n;i++)
		rg[lower_bound(x+1,x+1+n,x[i]+s[i]+1)-x-1].
			push_back(make_pair(lower_bound(x+1,x+1+n,x[i]-s[i])-x-1,c[i]));

	ll top=1;
	s[0]=0;c[1]=0;
	for(ll i=1;i<=n;i++){
		s[i]=1e18;
		for(size_t j=0;j<rg[i].size();j++)
			s[i]=min(s[i],s[c[lower_bound(c+1,c+1+top,rg[i][j].fi)-c]]+rg[i][j].se);
		while(top && s[i]<=s[c[top]])top--;
		c[++top]=i;
	}
	printf("%lld",s[n]);
	
	return 0;
}
