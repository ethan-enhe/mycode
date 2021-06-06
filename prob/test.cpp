#include<bits/stdc++.h>
using namespace std;
int n,arr[2][1005];
bool vis[1005];
inline int calmx(int side){
	memset(vis,0,sizeof(vis));
	int res=0;
	for(int i=n;i;i--){
		bool f=0;
		for(int j=n;j;j--)
			if(!vis[j] && arr[!side][j]<arr[side][i]){
				vis[j]=f=1,res+=3;
				break;
			}
		if(f)continue;
		for(int j=n;j;j--)
			if(!vis[j] && arr[!side][j]==arr[side][i]){
				vis[j]=f=1,res+=2;
				break;
			}
		if(!f)res++;
	}
	return res;
}
int main(){

	while(1){
		scanf("%d",&n);
		if(!n)break;
		for(int i=0;i!=2;i++){
			for(int j=1;j<=n;j++)
				scanf("%d",arr[i]+j);
			sort(arr[i]+1,arr[i]+1+n);
		}
		printf("%d %d\n",calmx(1),n*4-calmx(0));
	}
	return 0;
}
