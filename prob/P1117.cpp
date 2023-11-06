#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int MXN=2005;
const ull B=131;
int t,n;
char str[MXN];
ull h[MXN],pw[MXN];


inline ull gva(int l,int r){return h[r]-h[l-1]*pw[r-l+1];}
inline bool chk(int l,int r){
	int mid=(l+r)>>1;
	return gva(l,mid)==gva(mid+1,r);
}
inline void solve(){
	for(int i=1;i<=n;i++)h[i]=h[i-1]*B+str[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		int c1=0,c2=0;
		for(int j=i-1;j>0;j-=2)c1+=chk(j,i);
		if(!c1)continue;
		for(int j=i+2;j<=n;j+=2)c2+=chk(i+1,j);
		ans+=c1*c2;
	}
	printf("%d\n",ans);
}


int main(){
	freopen("test.in","r",stdin);
	pw[0]=1;
	for(int i=1;i!=MXN;i++)pw[i]=pw[i-1]*B;

	scanf("%d",&t);
	while(t--){
		scanf("%s",str+1);
		n=strlen(str+1);
		solve();
	}
	return 0;
}
