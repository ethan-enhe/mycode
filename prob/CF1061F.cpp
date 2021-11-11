#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
using namespace std;
const int MXN=1505;
int n,k,dpth;
bool res[MXN];
char tmp[10];
inline bool que(int x,int y,int z){
	printf("? %d %d %d\n",x,y,z);
	fflush(stdout);
	scanf("%s",tmp);
	return tmp[0]=='Y';
}
inline bool chk(int x,int y){
	memset(res,0,sizeof(0));
	int cnt=0;
	for(int i=1;i<=n;i++)
		cnt+=(res[i]=que(x,i,y));
	return cnt==dpth*2-1;
}
inline int dis(int x,int y){
	int r=0;
	for(int i=1;i<=n;i++)
		if(res[i])
			r+=que(x,i,y);
	return r;
}
int main(){
	srand(time(NULL));
	scanf("%d%d",&n,&k);
	dpth=log(n*(k-1)+1)/log(k)+1e-8;
	int x,y;
	while(1){
		x=rand()%n+1,y=rand()%n+1;
		if(chk(x,y))
			break;
	}
	for(int i=1;i<=n;i++)
		if(res[i] && dis(i,x)==dpth){
			printf("! %d\n",i);
			fflush(stdout);
			return 0;
		}
	return 0;
}
