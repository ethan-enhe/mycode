#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=1005;
const ll P=998244353;
ll n,m,cnt,arr[MXN];
ll mni[MXN],mxi[MXN],dp[MXN][MXN];

inline ll dfs(ll l,ll r){
	if(~dp[l][r])return dp[l][r];
	if(l>r)return 1;

	ll ci=MXN;
	if(l==r)ci=arr[l];
	else for(ll i=l;i<=r;i++)ci=min(ci,arr[i]);
	if(mni[ci]<l || mxi[ci]>r)return dp[l][r]=0;

	ll s1=0,s2=0;
	for(ll i=l;i<=mni[ci];i++)s1=(s1+dfs(l,i-1)*dfs(i,mni[ci]-1))%P;
	for(ll i=mxi[ci];i<=r;i++)s2=(s2+dfs(mxi[ci]+1,i)*dfs(i+1,r))%P;
	s1=s1*s2%P;
	for(ll last=mni[ci],i=last+1;i<=mxi[ci];i++)if(arr[i]==ci)s1=s1*dfs(last+1,i-1)%P,last=i;
	return dp[l][r]=s1;
}


int main(){
	//{{{ read
	scanf("%lld%lld",&n,&m);
	memset(mni,0x3f,sizeof(mni));
	ll last=-1;
	for(ll i=1,tmp;i<=m;i++){
		scanf("%lld",&tmp);
		if(tmp!=last)arr[cnt++]=last,last=tmp;
		mni[tmp]=min(mni[tmp],cnt);
		mxi[tmp]=max(mxi[tmp],cnt);
	}
	arr[cnt]=last;
	//}}}

	memset(dp,-1,sizeof(dp));
	printf("%lld",dfs(1,cnt));

	return 0;
}
