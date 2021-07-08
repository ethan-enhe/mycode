#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
const int MXN=1e5+5;

//vmx<=v0 && v0<=vmn

int n,m,v0[MXN],vmn[MXN],vmx[MXN];
int arr[MXN],dp[MXN];
inline bool cmp0(int x,int y){return v0[x]<v0[y];}
inline bool cmpmx(int x,int y){return vmx[x]<vmx[y];}


int s[MXN];
inline void clr(int x){for(;x<MXN;x+=x&(-x))s[x]=0;}
inline void mod(int x,int y){for(;x<MXN;x+=x&(-x))s[x]=max(s[x],y);}
inline int gmx(int x){int res=0;for(;x;x^=x&(-x))res=max(res,s[x]);return res;}

inline void cdq(int l,int r){
	if(l==r){
		dp[l]=max(dp[l],1);
		return;
	}
	int mid=(l+r)>>1,lind=l,rind=mid;
	cdq(l,mid);
	sort(arr+l,arr+mid+1,cmpmx);
	sort(arr+mid+1,arr+r+1,cmp0);
	while(++rind<=r){
		int cur=arr[rind];
		while(lind<=mid && vmx[arr[lind]]<=v0[cur]){
			mod(v0[arr[lind]],dp[arr[lind]]);
			lind++;
		}
		dp[cur]=max(dp[cur],gmx(vmn[cur])+1);
	}
	while(--lind>=l)clr(v0[arr[lind]]);
	for(int i=mid+1;i<=r;i++)arr[i]=i;
	cdq(mid+1,r);
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",v0+i);
		vmn[i]=vmx[i]=v0[i];
		arr[i]=i;
	}
	int tx,ty;
	while(m--){
		scanf("%d%d",&tx,&ty);
		vmn[tx]=min(vmn[tx],ty);
		vmx[tx]=max(vmx[tx],ty);
	}
	cdq(1,n);
	int ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	printf("%d",ans);
	return 0;
}
