#include<bits/stdc++.h>
using namespace std;
const int MXN=15;
const int NR=250;

int n,len[MXN+2][MXN];
string tmp[MXN];
int dp[1<<MXN][MXN],t[1<<MXN][MXN];
int main(){
	freopen("test.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;i++)cin>>tmp[i];
	sort(tmp,tmp+n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=min(tmp[i].size(),tmp[j].size());k;k--){
				bool f=1;
				for(int l=0;l<k;l++)
					if(tmp[j][l]!=tmp[i][tmp[i].size()-k+l]){
						f=0;
						break;
					}
				if(f)len[i][j]=k;
			}
	memset(dp,0x3f,sizeof(dp));
	dp[0][n]=0;
	for(int i=0;i<1<<n;i++)
		for(int j=0;j<=n;j++)
			if(((i>>j)&1 || (!i && j==n)) && dp[i][j]<=1e5){
				for(int k=0;k<n;k++)
					if(((i>>k)&1)==0){
						int ni=i^(1<<k),nv=dp[i][j]+(int)tmp[k].size()-len[j][k];
						if(dp[ni][k]>nv){
							dp[ni][k]=nv;
							t[ni][k]=j;
						}
					}
			}
	int ansj=0,ans=1e9;
	for(int j=n-1;j;j--)
		if(dp[(1<<n)-1][j]<ans)
			ans=dp[(1<<n)-1][j],ansj=j;
	cout<<ans<<endl;
	int stk[20],top;
	int ansi=(1<<n)-1;
	while(ansi){
		stk[++top]=ansj;
		int tmp=ansj;
		ansj=t[ansi][ansj];
		ansi^=1<<tmp;
	}
	stk[top+1]=-1;
	while(top){
		for(int i=t[stk[top+1]][stk[top]];i<tmp[stk[top]].size();i++)
			putchar(tmp[i][i]);

		top--;
	}


	return 0;
}
/*
int n;
//{{{ ac auto
struct node{
	char va;
	int fail,mark;
	int s[26];
}t[NR];
char tmp[MXN];
int nodec;
inline int ins(int ind){
	int len=strlen(tmp),p=0;
	for(int i=0;i<len;i++){
		int &nx=t[p].s[tmp[i]-'a'];
		if(!nx)t[nx=++nodec].va=tmp[i];
		p=nx;
	}
	t[p].mark|=1<<ind;
	return len;
}
inline void build(){
	queue<int> q;
	for(int i=0;i<26;i++)
		if(t[0].s[i])
			q.push(t[0].s[i]);
	while(!q.empty()){
		int p=q.front();q.pop();
		for(int i=0;i<26;i++){
			int &nx=t[p].s[i];
			if(nx){
				t[nx].fail=t[t[p].fail].s[i];
				q.push(nx);
			}
			else nx=t[t[p].fail].s[i];
		}
	}
	for(int i=0;i<=nodec;i++)
		for(int j=i;j;j=t[j].fail)
			t[i].mark|=t[j].mark;
}
//}}}
int dp[1<<MXN][MXN*MXN];
int main(){
	freopen("test.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",tmp);
		ins(i);
	}
	build();
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=1;
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<=nodec;j++){
			if(dp[i][j]>=1e5)continue;
			if(i==0 && j==3)cerr<<"!!!"<<dp[i][j];
			for(int k=0;k<26;k++){
				int nx=t[j].s[k];
				dp[i|t[nx].mark][nx]=min(dp[i|t[nx].mark][nx],dp[i][j]+1);
			}
		}
	int ans=1e9;
	for(int j=0;j<=nodec;j++)
		ans=min(ans,dp[(1<<n)-1][j]);
	printf("%d\n",ans);
	for(int i=0;i<=nodec;i++){
		cerr<<t[i].va<<" "<<t[i].fail<<" "<<t[i].mark<<endl;
		for(int j=0;j<26;j++)
			cerr<<t[i].s[j]<<" ";
		cout<<endl;
	}
	return 0;
}
*/
