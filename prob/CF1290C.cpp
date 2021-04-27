#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=3e5+5;
const ll INF=1e9;
char arr[MXN];
ll n,m,cnt[MXN],st[MXN][2];

inline ll id(ll x,ll y){return x+(y?m:0);}
ll fa[MXN<<1],sz[MXN<<1];
inline ll find(ll x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline bool merge(ll x,ll y){
	ll rx=find(x),ry=find(y);
	if(rx==ry)return 0;
	return fa[ry]=rx,sz[rx]+=sz[ry],1;
}
inline ll cal(ll x){return min(sz[find(x)],sz[find(x+m)]);}

int main(){
	scanf("%lld%lld %s",&n,&m,arr+1);
	for(ll i=1,tsz,tind;i<=m;i++){
		fa[i]=i,fa[i+m]=i+m,sz[i+m]=1;
		scanf("%lld",&tsz);
		while(tsz--){
			scanf("%lld",&tind);
			st[tind][cnt[tind]++]=i;
		}
	}
	for(ll i=1,ans=0;i<=n;i++){
		bool dig=arr[i]-'0';
		ans-=cal(st[i][0]);
		if(cnt[i]==1)sz[find(id(st[i][0],dig))]=INF;
		else{
			ll tmp=cal(st[i][1]);
			if(merge(st[i][0],id(st[i][1],dig^1)) && merge(st[i][0]+m,id(st[i][1],dig)))
				ans-=tmp;
		}
		ans+=cal(st[i][0]);
		printf("%lld\n",ans);
	}
	return 0;
}