#include<bits/stdc++.h>
using ll=long long;
using namespace std;
const int MXN=2e6+5;
int n,m;
char str[MXN];
int fa[MXN],sz[MXN];
int find(int x){
	while(x!=fa[x])
		x=fa[x]=fa[fa[x]];
	return x;
}
void mrg(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	fa[x]=y;
	sz[y]+=sz[x];
}
vector<int> vert[MXN];
int id(int x,int y){
	++x;
	return x+y*(m+2);
}
void imposs(){
	cout<<"impossible";
	exit(0);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	cin>>(str+1);
	for(int i=0;i<=m;i++){
		for(int j=0;j<3;j++){
			int idx=id(i,j);
			fa[idx]=idx;
			sz[idx]=j;
		}
	}
	for(int i=1;i<=m;i++){
		int t,x;
		cin>>t;
		while(t--){
			cin>>x;
			vert[x].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		while(vert[i].size()<2)vert[i].push_back(0);
		int v;
		if(str[i]=='R'){
			v=0;
		}
		else if(str[i]=='B'){
			v=1;
		}
		else{
			v=2;
		}
		for(int x=0;x<3;x++)
			for(int y=0;y<3;y++)
				if((x+y)%3==v){
					mrg(id(vert[i][0],x),id(vert[i][1],y));
				}
	}
//	for(int i=0;i<=m;i++){
//		for(int j=0;j<3;j++)
//			cout<<find(id(i,j))<<" ";
//		cout<<endl;
//	}
	if(find(id(0,0))==find(id(0,1)) || find(id(0,0))==find(id(0,2)))imposs();
	for(int i=1;i<=m;i++){
		int i0=find(id(i,0));
		int i1=find(id(i,1));
		int i2=find(id(i,2));
		int deter=find(id(0,0));
		int cnt=(i0==deter) +(i1==deter) +(i2==deter);
		if(cnt>1)imposs();
		else if(i0!=deter && i1!=deter && i2!=deter){
			if(i0==i1 && i1==i2)imposs();
			if(i1==i0){
				swap(i2,i0);
			}
			else if(i2==i0){
				swap(i1,i0);
			}
			else if(i1==i2){
			}
			else{
				if(sz[i0]>sz[i1])swap(i0,i1);
				if(sz[i0]>sz[i2])swap(i0,i2);
			}
			mrg(i0,id(0,0));
		}
	}
	
	cout<<sz[find(id(0,0))];
	return 0;
}
