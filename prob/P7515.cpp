#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll MXN=305;
ll t,n,m,arr[MXN][MXN],brr[MXN][MXN];
int main(int argc, char *argv[]){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=2;i<=n;i++)
			for(int j=2;j<=m;j++){
				scanf("%lld",&arr[i][j]);
				brr[i][j]=arr[i][j]-brr[i-1][j]-brr[i][j-1]-brr[i-1][j-1];
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
			}
	}
	
	return 0;
}
