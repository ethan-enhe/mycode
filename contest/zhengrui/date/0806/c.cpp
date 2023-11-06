#include<bits/stdc++.h>
using namespace std;

const int MXN=2e5+5;
struct ac{
	int ch[MXN][26],fail[MXN],mxw[MXN],nodec;
	inline ac(){memset(mxw,~0x3f,sizeof(mxw));}
	inline void insert(const string &s,int w){
		int p=0;
		for(int i=0;i<(int)s.size();i++){
			int tmp=s[i]-'a';
			if(!ch[p][tmp])ch[p][tmp]=++nodec;
			p=ch[p][tmp];
		}
		mxw[p]=w;
	}
	inline void build(){
		queue<int> q;
		for(int i=0;i<26;i++)
			if(ch[0][i])
				q.push(ch[0][i]);
		while(!q.empty()){
			int p=q.front();q.pop();
			mxw[p]=max(mxw[p],mxw[fail[p]]);
			for(int i=0;i<26;i++){
				int &nx=ch[p][i];
				if(nx){
					fail[nx]=ch[fail[p]][i];
					q.push(nx);
				}
				else nx=ch[fail[p]][i];
			}
		}
	}
}ori,rev;
string t[MXN];
char str[MXN];
int n,m,totlen,k,w[MXN],pre[MXN];
inline void solvek12(){
	ori.build();
	rev.build();
	memset(pre,~0x3f,sizeof(pre));
	for(int i=1,p=0;i<=n;i++){
		p=ori.ch[p][str[i]-'a'];
		pre[i]=max(pre[i-1],ori.mxw[p]);
	}
	if(k==1){
		printf("%d\n",max(pre[n],-1));
		return;
	}
	int ans=-1e9;
	for(int i=n,p=0,mx=-1e9;i;i--){
		p=rev.ch[p][str[i]-'a'];
		mx=max(mx,rev.mxw[p]);
		ans=max(ans,pre[i-1]+mx);
	}
	printf("%d",max(ans,-1));
}

int dp[MXN][4];
inline void force(){
	memset(dp,~0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i-1][0];
		for(int j=1;j<=k;j++){
			dp[i][j]=dp[i-1][j];
			for(int x=1;x<=m;x++){
				int len=t[x].size();
				if(i>=len){
					bool f=1;
					for(int y=1;y<=len;y++)
						if(str[i-y+1]!=t[x][len-y]){
							f=0;
							break;
						}
					if(f)dp[i][j]=max(dp[i][j],dp[i-len][j-1]+w[x]);
				}
			}
		}
	}
	printf("%d",max(-1,dp[n][k]));
}


int main(){
	scanf("%s%d%d",str+1,&m,&k);
	n=strlen(str+1);
	for(int i=1;i<=m;i++)cin>>t[i];
	for(int i=1;i<=m;i++){
		scanf("%d",w+i);
		ori.insert(t[i],w[i]);
		reverse(t[i].begin(),t[i].end());
		rev.insert(t[i],w[i]);
		reverse(t[i].begin(),t[i].end());
		totlen+=t[i].size();
	}
	if(k<=2)solvek12();
	else if(n<=1000 && totlen<=1000)force();
	else puts("0");

	return 0;
}
