#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=100000,P=998244353;
ll n,x[MXN],y[MXN];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		ll res=0;
		for(int j=1;j<=n;j++){
			ll tmp=abs(x[i]-x[j])+abs(y[i]-y[j]);
			tmp%=P;
			res=(res+tmp*tmp)%P;
		}
		cout<<res<<endl;
	}

	return 0;
}
