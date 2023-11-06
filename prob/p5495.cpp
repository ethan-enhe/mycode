#include<bits/stdc++.h>
using namespace std;
const int MXN=2e7+5;
const int MXP=5e6+5;
typedef unsigned int uint;
int n,p[MXP],pcnt;
bool isc[MXN];
uint seed,res,arr[MXN];
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
int main(){
	scanf("%d%u",&n,&seed);
	for(int i=2;i<=n;i++){
		if(!isc[i])p[++pcnt]=i;
		for(int j=1;p[j]*i<=n;j++){
			isc[p[j]*i]=1;
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)arr[i]=getnext();
	for(int i=1;i<=pcnt;i++)
		for(int j=1;j*p[i]<=n;j++)
			arr[j*p[i]]+=arr[j];
	for(int i=1;i<=n;i++)res^=arr[i];
	printf("%u",res);


	return 0;
}
