#include<bits/stdc++.h>
using namespace std;
//{{{ def
typedef long long ll;
struct edge{ll ter,w;};
template<class T>
struct myvec{
	T *d;ll top,sz;
	inline ll size(){return top;}
	inline T &operator [] (const ll &x)const{return d[x];}
	inline void pb(const T &x){
		if(top==sz)
			d=(T*)realloc(d,sizeof(T)*(sz=sz<<1|1));
		d[top++]=x;
	}
};

const ll MXN=1e6+5;
ll n,deg[MXN];
ll dpth[MXN],diam[MXN];
myvec<edge> e[MXN];
//}}}
//{{{ func
ll q[MXN<<1],ql=1,qr;
inline void topo(){
	for(ll i=1;i<=n;i++)
		if(deg[i]==1)
			q[++qr]=i;
	while(ql<=qr){
		ll p=q[ql++];
		for(ll i=0;i<e[p].size();i++){
			ll nx=e[p][i].ter;
			if(--deg[nx]){
				ll nd=dpth[p]+e[p][i].w;
				if(dpth[nx]<nd){
					diam[nx]=max(diam[nx],dpth[nx]+nd);
					diam[nx]=max(diam[nx],diam[p]);
					dpth[nx]=nd;
				}
				if(deg[nx]==1)q[++qr]=nx;
			}
		}
	}
}
ll dis[MXN<<1],tmp[MXN<<1],top;
inline ll f(ll i){return dpth[tmp[i]]-dis[i-1];}
inline ll solve(ll s){
	ll res=0;
	tmp[top=1]=s;
	do{
		deg[tmp[top]]=0,res=max(res,diam[tmp[top]]);
		tmp[top+1]=s;
		for(ll i=0;i<e[tmp[top]].size();i++){
			ll nx=e[tmp[top]][i].ter;
			if(deg[nx]==2 && nx!=tmp[top-1]){
				tmp[top+1]=nx;
				dis[top]=e[tmp[top]][i].w;
				break;
			}
		}
		if(tmp[top+1]==s)//回到起点
			for(ll i=e[tmp[top]].size();~i;i--)
				if(e[tmp[top]][i].ter==s){
					dis[top]=e[tmp[top]][i].w;
					break;
				}
	}while(tmp[++top]!=s);
	top--;
	for(ll i=1;i<=top;i++)
		tmp[i+top]=tmp[i],dis[i+top]=dis[i],dis[i]+=dis[i-1];
	for(ll i=top+1;i<=top<<1;i++)dis[i]+=dis[i-1];
	ql=1,qr=0;
	for(ll i=1;i<=top<<1;i++){
		while(ql<=qr && q[ql]+top<=i)ql++;
		if(ql<=qr)res=max(res,f(q[ql])+dpth[tmp[i]]+dis[i-1]);
		while(ql<=qr && f(i)>=f(q[qr]))qr--;
		q[++qr]=i;
	}
	return res;
}
//}}}
int main(){
	//freopen("test.in","r",stdin);
	scanf("%lld",&n);
	for(ll i=1,tt,tw;i<=n;i++){
		scanf("%lld%lld",&tt,&tw);
		e[i].pb(edge{tt,tw});
		e[tt].pb(edge{i,tw});
		deg[i]++,deg[tt]++;
	}
	topo();
	ll ans=0;
	for(ll i=1;i<=n;i++)
		if(deg[i]==2)
			ans+=solve(i);
	printf("%lld",ans);
	return 0;
}
