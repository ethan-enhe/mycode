
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN=100000,P=998244353;
ll n,x[MXN],y[MXN];

int main(){
	ll t=100;
	while(t--){
		system("./Ag>A.in");
		system("./A<A.in>A.out");
		system("./Af<A.in>Af.out");
		if(system("diff A.out Af.out -Z")){
			break;

		}
		else cout<<t<<endl;

	}
	return 0;
}
