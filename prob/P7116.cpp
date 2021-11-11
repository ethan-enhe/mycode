#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int MXN=1e6+5,MXK=11;
struct pi{
	int x,y;
	inline void prt(){
		printf("(%d,%d)",x,y);
	}
}op[MXN],bound[MXN][MXK];
int n,k,w[MXK],go[MXK],tmp[MXK];
inline int upd(pi &x,int y){
	if(y<x.x)return x.x=y,-1;
	if(y>x.y)return x.y=y,1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
		scanf("%d",w+i);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&op[i].x,&op[i].y);
		go[op[i].x]+=op[i].y;
	}
	for(int i=1;i<=n;i++){
		if(go[op[i].x]<0)
			op[i].y=-op[i].y;
		op[i+n]=op[i];
	}
	for(int i=1;i<=k;i++)
		go[i]=abs(go[i]);
	for(int i=1;i<=n;i++){
		tmp[op[i].x]+=op[i].y;
		int tres=1;
		for(int j=1;j<=k;j++){
			bound[i][j]=bound[i-1][j];
			if(j!=op[i].x)tres*=w[j]+1-bound[i][j].y+bound[i][j].x;
		}
		int type=upd(bound[i][op[i].x],tmp[op[i].x]);
		for(int j=1;j<=k;j++)
			cout<<tmp[j]<<" ";
		cout<<endl;
		for(int j=1;j<=k;j++)
			bound[i][j].prt();
		cout<<endl;
		cout<<tres<<endl;
	}
	return 0;
}
