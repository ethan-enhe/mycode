#include<bits/stdc++.h>
using namespace std;
const int MXN=525020;
const int MXD=20;
int n,arr[MXN];
vector<int> e[MXN];
int rt[MXN],nodec;long long ans;
struct node{
	int son[2],va,cnt;
	node(){son[0]=son[1]=va=cnt=0;}
}t[MXN*(MXD+1)];
inline void pushup(int p){
	t[p].cnt=t[t[p].son[0]].cnt^t[t[p].son[1]].cnt;
	t[p].va=((t[t[p].son[0]].va^t[t[p].son[1]].va)<<1)|t[t[p].son[1]].cnt;
}
inline void insert(int &p,int x,int dpth){
	if(!p)p=++nodec;
	if(dpth>MXD){
		t[p].cnt^=1;
		return;
	}
	insert(t[p].son[(x>>dpth)&1],x,dpth+1);
	pushup(p);
}
inline void add1(int p){
	if(t[p].son[1])add1(t[p].son[1]);
	swap(t[p].son[0],t[p].son[1]);
	pushup(p);
}
inline int merge(int lr,int rr,int dpth){
	if(!lr || !rr)return lr^rr;
	if(dpth==MXD+1){
		t[lr].cnt^=t[rr].cnt;
		return lr;
	}
	t[lr].son[0]=merge(t[lr].son[0],t[rr].son[0],dpth+1);
	t[lr].son[1]=merge(t[lr].son[1],t[rr].son[1],dpth+1);
	pushup(lr);
	return lr;
}

inline void dfs(int p){
	for(size_t i=0;i<e[p].size();i++){
		int nx=e[p][i];
		dfs(nx);
		rt[p]=merge(rt[p],rt[nx],0);
	}
	add1(rt[p]);
	insert(rt[p],arr[p],0);
	ans+=t[rt[p]].va;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",arr+i);
	for(int i=2;i<=n;i++){
		int tmp;
		scanf("%d",&tmp);
		e[tmp].push_back(i);
	}
	dfs(1);
	printf("%lld",ans);
	return 0;
}
