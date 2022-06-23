#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const char nl='\n';
const ll MXN=8,P=1e9+7,INV100=570000004,NR=4e7;
ll n;
ll id[MXN][MXN],idc;
ll p[MXN*MXN],invp[MXN*MXN];
ll qpow(ll x,ll y){
	ll r=1;
	while(y){
		if(y&1)r=r*x%P;
		x=x*x%P,y>>=1;
	}
	return r;
}
ll sp[NR];
bool f[NR];

ll arr[MXN];
int main(){
	/*
	assert(INV100*100%P==1);
	cerr<<(sizeof(sp)>>20);
	*/
	freopen("ne.in","r",stdin);
	freopen("ne.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	sp[0]=1;
	cin>>n;
	for(ll i=1;i<=n;i++){
		arr[i]=i;
		for(ll j=1;j<=n;j++){
			ll x;
			cin>>x;
			if(x==0)id[i][j]=-2;
			else if(x==100)id[i][j]=-1;
			else{
				id[i][j]=idc;
				p[idc]=INV100*x%P;
				invp[idc]=p[idc]*qpow(1-p[idc],P-2)%P;
				sp[0]=sp[0]*(1-p[idc])%P;
				++idc;
			}
		}
	}
	do{
		ll s=0;
		for(ll i=1;i<=n;i++){
			ll cid=id[i][arr[i]];
			if(cid==-2){
				s=-1;
				break;
			}
			else if(cid>=0)
				s|=1<<cid;
		}
		if(s>=0)f[s]=1;
	}while(next_permutation(arr+1,arr+1+n));

	for(ll h=0,w=1,w2=2;h<idc;h++,w<<=1,w2<<=1)
		for(ll i=0;i<(1<<idc);i+=w2)
			for(ll j=0;j<w;j++)
				f[i+j+w]|=f[i+j];

	ll ans=0;
	for(ll i=0;i<(1<<idc);i++){
		if(i){
			ll lbt=i&(-i),lglbt=__builtin_ctz(lbt);
			sp[i]=sp[i-lbt]*invp[lglbt]%P;
			if(f[i])ans=(ans+sp[i])%P;
		}
	}
	cout<<(ans+P)%P;
	return 0;
}

