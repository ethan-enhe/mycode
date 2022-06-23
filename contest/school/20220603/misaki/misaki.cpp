#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const char nl='\n';
const ll MXN=2e6+5,LG=100;
ll magic[MXN];
ll l[MXN],c[MXN];
ll mylog(ll x){
	return 31-__builtin_clz(x);
}
void gen(ll x,ll *res){
	ll hbt=1<<mylog(x),nx=x^hbt;
	if(nx)gen(nx,res);
	ll nxe=nx?res[nx-1]:0,ind=-1;
	for(ll i=0;i<hbt;i++)
		if(nxe==magic[i]){
			ind=i;
			break;
		}
	ll tmp=nx;
	for(ll i=ind;i<hbt;i++)
		res[tmp++]=magic[i];
	for(ll i=0;i<ind;i++)
		res[tmp++]=magic[i];
	for(ll i=0;i<nx;i++)
		res[i]+=hbt;
}
ll n,m;
ll dp[LG][LG];
bool f[LG][LG];

ll mrg(ll a,ll b){
	if(n==1 || m==1)return a|b;
	ll ln=mylog(n-1)+1,lm=mylog(m-1)+1;
	ll x=0,y=0,r=0;
	while(x<ln || y<lm){
		//cerr<<f[x][y];
		if(f[x][y]){
			r^=(b&1)<<(x+y);
			b>>=1;
			y++;
		}
		else{
			r^=(a&1)<<(x+y);
			a>>=1;
			x++;
		}
	}
	return r;
}


int main(){
	freopen("misaki.in","r",stdin);
	freopen("misaki.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	magic[0]=0;
	for(ll i=1;i<MXN;i++){
		ll hbt=mylog(i);
		magic[i]=magic[(1<<(hbt+1))-i-1]+(1<<hbt);
	}
	cin>>n>>m;
	gen(n,l);
	gen(m,c);
	--n,--m;
	if(n && m){
		memset(dp,0x3f,sizeof(dp))
		ll ln=mylog(n)+1,lm=mylog(m)+1;
		dp[ln][lm]=0;
		for(ll i=ln;~i;i--)
			for(ll j=lm;~j;j--){
				if(i){
					ll nxd=dp[i][j]+(((n>>(i-1))&1)<<(i+j-1));
					if(nxd<dp[i-1][j]){
						dp[i-1][j]=nxd;
						f[i-1][j]=0;
					}
				}
				if(j){
					ll nxd=dp[i][j]+(((m>>(j-1))&1)<<(i+j-1));
					if(nxd<dp[i][j-1]){
						dp[i][j-1]=nxd;
						f[i][j-1]=1;
					}
				}
			}
	}
	//cerr<<mrg(2,3);
	++n,++m;
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++)
			cout<<mrg(l[i],c[j])<<" ";
		cout<<nl;
	}



	return 0;
}

