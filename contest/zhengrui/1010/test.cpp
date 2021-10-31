#include<bits/stdc++.h>
using namespace std;
const int NR=405;
const int mod=1e9+7;
void Add(int& x,int y){x=(x+y>=mod)?x+y-mod:x+y;}
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,k;
int a[NR],b[NR];
int cnt[NR];
int dp[NR][NR],f[NR];
int fac[NR],inv[NR],invv[NR];
void init(){
	int lim=400;fac[0]=inv[0]=inv[1]=invv[0]=1;
	for(int i=1;i<=lim;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=lim;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=lim;i++)invv[i]=1ll*invv[i-1]*inv[i]%mod;
}
int C(int a,int b){
	return 1ll*fac[a]*invv[b]%mod*invv[a-b]%mod;
}
int calc(int x)
{
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)cnt[i]=lower_bound(b+1,b+n+1,x-a[i])-b-1;
//	for(int i=1;i<=n;i++)cnt[i]=n-cnt[i];
	sort(cnt+1,cnt+n+1);
	
	memset(dp,0,sizeof(dp));dp[0][0]=1;
	for(int i=0;i<=n;i++){
		cerr<<cnt[i+1]<<endl;
		for(int j=0;j<=i;j++){
			Add(dp[i+1][j],dp[i][j]);
			Add(dp[i+1][j+1],1ll*dp[i][j]*(cnt[i+1]-j)%mod);
		}
	}
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=0;j<=i;j++)
			cout<<dp[i][j]<<" ";
	for(int i=0;i<=n;i++){
		dp[n][i]=1ll*dp[n][i]*fac[n-i]%mod;
	}

//	if(x<=10){
//		for(int i=0;i<=n;i++)cout<<dp[n][i]<<endl;puts("");
//	}
	memset(f,0,sizeof(f));
	for(int i=0;i<=n;i++)
	{
		int now=1;
		for(int j=i;j<=n;j++,now*=-1){
			if(now<0)now+=mod;
			Add(f[i],1ll*now*dp[n][j]%mod*C(j,i)%mod);
		}
	}

	int res=0;
	for(int i=0;i<=n-k;i++)Add(res,f[i]);
	return res;
}
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=1ll*res*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}return res;
}
int ans[NR<<1];
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),k=read();init();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1);
	calc(6);
	/*
	for(int i=1;i<=800;i++)ans[i]=calc(i);
	int Ans=0;
	for(int i=1;i<=800;i++)
		Add(Ans,1ll*i*(ans[i]-ans[i+1]+mod)%mod);
	printf("%lld\n",1ll*Ans*ksm(fac[n],mod-2)%mod);
	*/
	return 0;
}

