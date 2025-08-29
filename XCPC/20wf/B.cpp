
#include<bits/stdc++.h>
using namespace std;
const int MXN=20005;
int n,c;

struct seg{
	int l,k,b;
	seg operator + (const seg &y)const{
		return seg{max(l,y.l),k+y.k,b+y.b};
	}
	int operator () (const int &y)const{
		return y*k+b;
	}
};
vector<pair<int,int>> g[MXN];
void prt(const vector<seg> &x){
	for(auto[l,k,b] : x){
		cerr<<l<<","<<k<<","<<b<<" ";
	}
	cerr<<endl;
}
vector<seg> mrg(const vector<seg> &x,const vector<seg> &y){
	cerr<<"mrg"<<endl;
	prt(x);
	prt(y);
	vector<seg> res;
	if(x.empty() || y.empty()) return res;
	int ix=0,iy=0;
	seg lstx={0,0,0},lsty={0,0,0};

	if(x[0].l<=y[0].l){
		lstx=x[ix++];
	}
	else 
		lsty=y[iy++];

	while(ix<x.size() && iy<y.size()){
		if(x[ix].l==y[iy].l){
			res.push_back(x[ix]+y[iy]);
			lstx=x[ix++];
			lsty=y[iy++];
		}
		else if(x[ix].l<y[iy].l){
			res.push_back(x[ix]+lsty);
			lstx=x[ix++];
		}
		else{
			res.push_back(y[iy]+lstx);
			lsty=y[iy++];
		}
	}
	while(ix<x.size()){
		res.push_back(x[ix]+lsty);
		lstx=x[ix++];
	}
	while(iy<y.size()){
		res.push_back(y[iy]+lstx);
		lsty=y[iy++];
	}
	cerr<<"done";
	prt(res);
	return res;
}
void umn(vector<seg> &x,seg y){
	int idx=x.size();
	while(idx && y(x[idx-1].l)<=x[idx-1](x[idx-1].l)){
		--idx;
	}
	x.resize(idx);
	y.l=
	x.push_back(y);
}
int getmn(const vector<seg> &x){
	return x[0](x[0].l);
}

vector<seg> dfs(int p,int fa,int faw){
	cerr<<p<<endl;
	vector<seg> res;
	if(fa)res={seg{faw,1,-faw}};
	else res={seg{0,0,0}};
	int sum_mn=0;
	for(auto [nx,nxw]:g[p])
		if(nx!=fa){
			auto tmp=dfs(nx,p,nxw);
			res=mrg(res,tmp);
			sum_mn+=getmn(tmp);
		}
	umn(res,seg{faw,1,-faw+sum_mn+c*g[p].size()});
	cerr<<p<<endl;
	prt(res);
	return res;
}
int main(){
	freopen("test.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>c;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		cerr<<u<<" "<<v<<endl;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	cout<<getmn(dfs(1,0,0));
	return 0;
}


