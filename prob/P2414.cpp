#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef pair<int,int> pi;
const int MXN=1e5+5;

char str[MXN];int q,ans[MXN];



vector<pi> que[MXN];
int t[MXN][26],fail[MXN],endp[MXN];
int ind,strc,nodec;
inline void bldtrie(int p){
	while(str[++ind]){
		if(str[ind]=='P')endp[++strc]=p;
		else if(str[ind]=='B')return;
		else{
			int tmp=str[ind]-'a';
			if(!t[p][tmp])t[p][tmp]=++nodec;
			bldtrie(t[p][tmp]);
		}
	}
}
vector<int> e[MXN];
inline int find(int p,int x){
	if(t[p][x])return t[p][x];
	return p?find(fail[p],x):0;
}
inline void bldfail(){
	queue<int> q;
	for(int i=0;i<26;i++)
		if(t[0][i])
			q.push(t[0][i]);
	while(!q.empty()){
		int p=q.front();q.pop();
		e[fail[p]].pb(p);
		for(int i=0;i<26;i++){
			int nx=t[p][i];
			if(nx){
				fail[nx]=find(fail[p],i);
				q.push(nx);
			}
		}
	}
}

int d[MXN];
inline void mod(int x,int y){for(;x<=nodec;x+=x&(-x))d[x]+=y;}
inline int sum(int x){int r=0;for(;x;x^=x&(-x))r+=d[x];return r;}

int dfl[MXN],dfr[MXN],dfsc;
inline void dfsi(int p,int fa){
	dfl[p]=++dfsc;
	for(int nx:e[p])
		if(nx!=fa)
			dfsi(nx,p);
	dfr[p]=dfsc;
}
inline void dfsq(int p){
	mod(dfl[p],1);
	for(pi cq:que[p])
		ans[cq.se]=sum(dfr[cq.fi])-sum(dfl[cq.fi]-1);
	for(int i=0;i<26;i++)
		if(t[p][i])
			dfsq(t[p][i]);
	mod(dfl[p],-1);
}
int main(){
	scanf("%s%d",str+1,&q);
	bldtrie(0);
	for(int i=1,tx,ty;i<=q;i++){
		scanf("%d%d",&tx,&ty);
		que[endp[ty]].pb(mp(tx,i));
	}
	bldfail();
	dfsi(0,-1);
	dfsq(0);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
