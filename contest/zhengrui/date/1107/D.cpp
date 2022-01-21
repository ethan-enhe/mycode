#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double db;
const ll MXN=1e6+5;
ll n,m,arr[MXN];
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",arr+i);
	for(int i=1;i<=n;i++){
		ll tmp;
		scanf("%lld",&tmp);
		db r=0;
		for(int j=1;j<=n;j++)
			r+=(db)tmp/(arr[j]+tmp);
		printf("%.9Lf ",r+1e-11);

	}

	return 0;
}

