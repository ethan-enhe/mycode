#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
const ll MXN=105;
const ll INF=1e18;
const ll LG=34;

ll n,m,q;
struct mat{
	ll mx[MXN][MXN],mn[MXN][MXN];
	mat(){
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=n;j++)
				mx[i][j]=-INF,mn[i][j]=INF;
	}
	mat operator * (const mat &b)const{
		mat res;
		for(ll i=1;i<=n;i++)
			for(ll k=1;k<=n;k++)
				for(ll j=1;j<=n;j++){
					res.mx[i][j]=max(res.mx[i][j],mx[i][k]+b.mx[k][j]);
					res.mn[i][j]=min(res.mn[i][j],mn[i][k]+b.mn[k][j]);
				}
		return res;
	}
}A[LG];
mat dot(const mat &x,const mat &y,ll i){
	mat res;
	for(ll k=1;k<=n;k++)
		for(ll j=1;j<=n;j++){
			res.mx[i][j]=max(res.mx[i][j],x.mx[i][k]+y.mx[k][j]);
			res.mn[i][j]=min(res.mn[i][j],x.mn[i][k]+y.mn[k][j]);
		}
	return res;
}
void que(ll u,ll v,ll k){
	mat res;
	res.mx[u][u]=res.mn[u][u]=0;
	for(ll i=LG-1;~i;i--)
		if((k>>i)&1)
			res=dot(res,A[i],u);
	if(res.mx[u][v]<0)cout<<"-1 -1\n";
	else cout<<res.mn[u][v]<<" "<<res.mx[u][v]<<'\n';
}

void umn(ll &x,ll y){
	x=min(x,y);
}
void umx(ll &x,ll y){
	x=max(x,y);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	//assert(A.mx[0][0]*2>=0);
	cin>>n>>m>>q;

	A[0]=mat();
	//cout<<A[0].mn[1][2];
	while(m--){
		ll u,v,w;
		cin>>u>>v>>w;
		umn(A[0].mn[u][v],w);
		umn(A[0].mn[v][u],w);
		umx(A[0].mx[u][v],w);
		umx(A[0].mx[v][u],w);
	}
	for(ll i=1;i<LG;i++){
		A[i]=A[i-1]*A[i-1];
	}
	while(q--){
		ll u,v,k;
		cin>>u>>v>>k;
		que(u,v,k);
	}
	return 0;
}


