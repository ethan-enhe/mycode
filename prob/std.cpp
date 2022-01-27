#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
const int MR=1005;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,p,st;
char s[NR],tp[NR],t[NR];
bitset<MR>dp[NR],f[30];
int solve(int st,int m)
{
	if(!m)return st-1;
	for(int i=1;i<=26;i++)f[i].reset();
	for(int i=1;i<=m;i++){
		if(t[i]<='z'&&t[i]>='a')f[t[i]-'a'+1].set(i);
		else for(int j=1;j<=26;j++)f[j].set(i);
	}
//	cout<<st<<" "<<m<<" "<<t[1]<<endl;
	dp[st-1].reset(),dp[st-1].set(0);
	for(int i=st;i<=n;i++){
		dp[i]=((dp[i-1]<<1)&f[s[i]-'a'+1]);
		dp[i].set(0);
//		if(m==4&&i==5)cout<<"***"<<dp[i][4]<<endl;
//		if(dp[i][4])cout<<"(((((("<<i<<endl;
		if(dp[i][m])return i;
	}
	return -1;
}
void work()
{
	scanf("%s",tp+1),p=strlen(tp+1);
	bool flag=0;st=1;m=0;
	int S=0,E=0;tp[p+1]='*';
	for(int i=1;i<=p+1;i++){
		if(tp[i]=='*'){
			int sta=solve(st,m);
			if(sta==-1){puts("0 0");return;}
			if(!flag)S=sta-m+1;
			if(i==p+1)E=sta;
			st=sta+1;m=0;flag=1;
		}
		else t[++m]=tp[i];
	}
	printf("%d %d\n",S,E);
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%s",s+1),n=strlen(s+1);
	int T=read();while(T--)work();
	return 0;
}
