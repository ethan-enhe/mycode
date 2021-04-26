#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rd scanf
#define pt printf
#define setp(x) setprecision(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define sz(x) (int)x.size()
#define umn(x,y) x=min(x,y)
#define umx(x,y) x=max(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pi;
typedef queue<ll> qi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

const ll INF=1e18;
const ll P=1e9+7;
const ll MXN=45;

inline ll mod(const ll &x){return x>=P?x-P:x;}
inline ll mul(ll x,ll y){if(x<y)swap(x,y);ll res=0;while(y){if(y&1)res=mod(res+x);x=mod(x<<1);y>>=1;}return res;}
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%P;x=x*x%P;y>>=1;}return res;}
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline void pbin(ll x,ll y){for(;~y;y--)cerr<<char('0'+((x>>y)&1));cerr<<endl;}



ll n,top;
ll cnt[MXN][MXN][MXN],dp[MXN][MXN][MXN][MXN];
struct vec{
	ll x,y;
	vec(ll x=0,ll y=0):x(x),y(y){}
	vec operator + (const vec &b)const{return vec(x+b.x,y+b.y);}
	vec operator - (const vec &b)const{return vec(x-b.x,y-b.y);}
	ll operator * (const vec &b)const{return x*b.y-b.x*y;}
}arr[MXN];
inline bool intri(const vec &x,const vec &a,const vec &b,const vec &c){
	ll res_ab=(b-a)*(x-a);
	ll res_bc=(c-b)*(x-b);
	ll res_ca=(a-c)*(x-c);
	return (res_ab>0 && res_bc>0 && res_ca>0) || (res_ab<0 && res_bc<0 && res_ca<0);
}
inline bool expand(const ll &x,ll &a,ll &b,ll &c){
	if(intri(arr[a],arr[x],arr[b],arr[c]))a=x;
	else if(intri(arr[b],arr[x],arr[c],arr[a]))b=x;
	else if(intri(arr[c],arr[x],arr[a],arr[b]))c=x;
	else return 0;

	if(a>b)swap(a,b);
	if(b>c)swap(b,c);
	if(a>b)swap(a,b);

	return 1;
}
struct status{
	ll i,j,k;
	bool operator < (const status &b)const{return cnt[i][j][k]<cnt[b.i][b.j][b.k];}
}sta[MXN*MXN*MXN];
inline void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&arr[i].x,&arr[i].y);

	ll mx=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++){
				for(int l=1;l<=n;l++)
					cnt[i][j][k]+=intri(arr[l],arr[i],arr[j],arr[k]);
				mx=max(mx,cnt[i][j][k]);
				dp[i][j][k][0]=6;
				sta[++top]=status{i,j,k};
			}
	if(mx<n-3){
		printf("0");
		return;
	}
	sort(sta+1,sta+1+top);
	//当前边框为i，j，k，边框内选了l个
	for(int stai=1;stai<=top;stai++){
		ll i=sta[stai].i,j=sta[stai].j,k=sta[stai].k;

		ll tmp=cnt[i][j][k],ni,nj,nk;
		for(int l=0;l<=tmp;l++){
			dp[i][j][k][l+1]=(dp[i][j][k][l+1]+dp[i][j][k][l]*(cnt[i][j][k]-l))%P;
			ni=i,nj=j,nk=k;
			for(int m=1;m<=n;m++)
				if(expand(m,ni,nj,nk)){
					dp[ni][nj][nk][l+1]=mod(dp[ni][nj][nk][l+1]+dp[i][j][k][l]);
					ni=i,nj=j,nk=k;
				}
		}
	}
	printf("%lld",dp[sta[top].i][sta[top].j][sta[top].k][n-3]);
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	srand(time(NULL));

	ll tq=1;
	while(tq--)solve();
	return 0;
}
