#include<bits/stdc++.h>
using namespace std;
//{{{ def
typedef long long ll;
typedef pair<ll,ll> pi;
const ll MXLG=31;
const ll MXM=505;
const ll MXN=51;
const ll MXW=5;
const ll MXSZ=MXN*MXW;
ll n,m,t,k,c[MXN],sz;
struct fest{ll tt,tx,ty;}f[MXW];
//}}}

//{{{ mat
struct mat{
	ll arr[MXSZ][MXSZ];
	inline mat(bool isunit=0){
		memset(arr,~0x3f,sizeof(arr));
		if(isunit)for(ll i=1;i<=sz;++i)arr[i][i]=0;
	} 
	inline mat operator * (const mat &b)const{
		mat res;
		for(ll i=1;i<=sz;++i)
			for(ll j=1;j<=sz;++j)
				for(ll l=1;l<=sz;++l)
					res.arr[i][j]=max(res.arr[i][j],arr[i][l]+b.arr[l][j]);
		return res;
	}
	inline mat operator - (const mat &b)const{
		mat res;
		for(ll j=1;j<=sz;++j)
			for(ll l=1;l<=sz;++l)
				res.arr[1][j]=max(res.arr[1][j],arr[1][l]+b.arr[l][j]);
		return res;
	}
	inline mat operator ^ (ll y)const{
		mat res,x=*this;
		while(y){
			if(y&1)res=res*x;
			x=x*x;
			y>>=1;
		}
		return res;
	}
}trans[MXLG+1],res;
//}}}

//{{{ func
inline bool cmp(fest x,fest y){return x.tt<y.tt;}
inline ll id(ll x,ll y){return (x-1)*n+y;}
inline void cal(ll len){
	for(ll i=MXLG;~i;i--){
		if((len>>i)&1)
			res=res-trans[i];
	}
}
//}}}
int main(){
	freopen("test.in","r",stdin);
	scanf("%lld%lld%lld%lld",&n,&m,&t,&k);
	sz=n*MXW,trans[0]=mat(),res=mat();
	for(ll i=1;i<=n;++i){
		scanf("%lld",c+i);
		//res.arr[1][id(MXW,i)]=0;
	}
	res.arr[1][id(MXW,1)]=c[1];
	
	for(ll i=1,ts,tt,tw;i<=m;++i){
		scanf("%lld%lld%lld",&ts,&tt,&tw);
		trans[0].arr[id(MXW-tw+1,ts)][id(MXW,tt)]=c[tt];
	}
	for(int i=1;i<MXW;++i)
		for(int j=1;j<=n;++j)
			trans[0].arr[id(i+1,j)][id(i,j)]=0;
	for(int i=1;i<=MXLG;++i)
		trans[i]=trans[i-1]*trans[i-1];

	for(int i=1;i<=k;++i)
		scanf("%lld%lld%lld",&f[i].tt,&f[i].tx,&f[i].ty);
	sort(f+1,f+1+k,cmp);f[0].tt=0;
	for(int i=1;i<=k;++i){
		cal(f[i].tt-f[i-1].tt);
		res.arr[1][id(MXW,f[i].tx)]+=f[i].ty;
	}
	
	cal(t-f[k].tt);
	ll ans=res.arr[1][id(MXW,1)];
	printf("%lld",ans<0?-1:ans);

	return 0;
}
