#include<bits/stdc++.h>
using namespace std;
const int MXN=1e8+5,MXP=1e7+5;
bool isc[MXN];
int n,q,pri[MXN],ind;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++){
		if(!isc[i])pri[++ind]=i;
		for(int j=1;pri[j]*i<=n;j++){
			isc[pri[j]*i]=1;
			if(i%pri[j]==0)break;
		}
	}
	while(q--){
		int tmp;
		scanf("%d",&tmp);
		printf("%d\n",pri[tmp]);
	}
	return 0;
}
