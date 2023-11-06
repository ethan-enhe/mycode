#include<bits/stdc++.h>
using namespace std;
const int MXN=25;
int n,x[MXN],y[MXN];
bool s[MXN];
inline int nx(int x){
	x++;
	if(x>(n<<1))
		x-=(n<<1);
	return x;
}
inline bool dfs(int num){
	if(!num){
		for(int i=1;i<=n;i++)
			if((s[x[i]]^s[y[i]])==0)
				return 0;
		for(int i=1;i<=(n<<1);i++){
			int t1=nx(i),t2=nx(t1);
			if(s[i]==s[t1] && s[t1]==s[t2])
				return 0;
		}
		for(int i=1;i<=(n<<1);i++)
			putchar('X'+s[i]);
			//putchar('0'+s[i]);
		putchar('\n');
		return 1;
	}
	s[num]=1;
	if(dfs(num-1))return 1;
	if(num!=(n<<1)){
		s[num]=0;
		if(dfs(num-1))return 1;
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",x+i,y+i);
	if(!dfs(n<<1))printf("Impossible");
	return 0;
}
