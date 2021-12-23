#include <bits/stdc++.h>
using namespace std;
const double INF=1e9;
const int MXC=10,MXS=1505;
struct node{
	int son[MXC],fail,cnt;
	double va;
}t[MXS];
int n,m,nodec;
char str[MXS],tmp[MXS];
double dp[MXS][MXS],l,r,mid;
int prej[MXS][MXS],prec[MXS][MXS];
int q[MXS],ql=1,qr;
void ins(double w){
	int len=strlen(tmp+1),p=0;
	for(int i=1;i<=len;i++){
		int &nx=t[p].son[tmp[i]-'0'];
		if(!nx)nx=++nodec;
		p=nx;
	}
	r=max(r,w);
	t[p].va+=w;
	t[p].cnt++;
}
void build(){
	for(int i=0;i<MXC;i++)
		if(t[0].son[i])
			q[++qr]=t[0].son[i];
	while(ql<=qr){
		int p=q[ql++];
		for(int i=0;i<MXC;i++){
			int &nx=t[p].son[i],nxf=t[t[p].fail].son[i];
			if(nx){
				t[nx].fail=nxf;
				q[++qr]=nx;
			}
			else nx=nxf;
		}
	}
	for(int i=1;i<=nodec;i++){
		node &cur=t[q[i]];
		cur.va+=t[cur.fail].va;
		cur.cnt+=t[cur.fail].cnt;
	}
}
#define trans(x) {\
	int nxj=t[j].son[x];\
	double nxv=dp[i][j]+t[nxj].va-rate*t[nxj].cnt;\
	if(nxv>dp[i+1][nxj])\
		dp[i+1][nxj]=nxv;\
}
bool cal(double rate){
	fill(dp[0],dp[0]+1+nodec,-INF);
	dp[0][0]=0;
	for(int i=0;i<n;i++){
		fill(dp[i+1],dp[i+1]+1+nodec,-INF);
		if(str[i+1]!='.'){
			for(int j=0;j<=nodec;j++)
				trans(str[i+1]-'0');
		}
		else for(int j=0;j<=nodec;j++){
			trans(0);trans(1);trans(2);trans(3);trans(4);
			trans(5);trans(6);trans(7);trans(8);trans(9);
		}
	}
	for(int i=0;i<=nodec;i++)
		if(dp[n][i]>0)
			return 1;
	return 0;
}
#define transm(x) {\
	int nxj=t[j].son[x];\
	double nxv=dp[i][j]+t[nxj].va-rate*t[nxj].cnt;\
	if(nxv>dp[i+1][nxj]){\
		dp[i+1][nxj]=nxv;\
		prec[i+1][nxj]=x;\
		prej[i+1][nxj]=j;\
	}\
}
bool calm(double rate){
	fill(dp[0],dp[0]+1+nodec,-INF);
	dp[0][0]=0;
	for(int i=0;i<n;i++){
		fill(dp[i+1],dp[i+1]+1+nodec,-INF);
		if(str[i+1]!='.'){
			for(int j=0;j<=nodec;j++)
				transm(str[i+1]-'0');
		}
		else for(int j=0;j<=nodec;j++){
			transm(0);transm(1);transm(2);transm(3);transm(4);
			transm(5);transm(6);transm(7);transm(8);transm(9);
		}
	}
	for(int i=0;i<=nodec;i++)
		if(dp[n][i]>0)
			return 1;
	return 0;
}

int main(){
	int en=clock()+0.2*CLOCKS_PER_SEC;
	scanf("%d%d%s",&n,&m,str+1);
	while(m--){
		int w;
		scanf("%s%d",tmp+1,&w);
		ins(log(w));
	}
	build();
	while(clock()<en && r-l>1e-6*(r)){
		mid=(l+r)/2;
		if(cal(mid))l=mid;
		else r=mid;
	}
	calm(l);
	for(int i=0;i<=nodec;i++)
		if(dp[n][i]>0){
			for(int j=n;j;j--){
				str[j]='0'+prec[j][i];
				i=prej[j][i];
			}
			printf("%s",str+1);
			return 0;
		}
}
