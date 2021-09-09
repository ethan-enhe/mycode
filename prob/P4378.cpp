#include<bits/stdc++.h>
const int MXN=1e5+5,INF=1e9;
std::unordered_map<int,int> pre;
inline void mod(int x){
	for(;x;x^=x&(-x))
		pre[x]++;
}
inline int que(int x){
	int res=0;
	for(;x<=INF;x+=x&(-x))
		res+=pre[x];
	return res;
}
int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1,tmp;i<=n;i++){
		scanf("%d",&tmp);
		ans=std::max(ans,que(tmp+1));
		mod(tmp);
	}
	printf("%d",ans+1);

	return 0;
}
