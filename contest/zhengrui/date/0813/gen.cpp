#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MX=1e18;
mt19937_64 myrand(time(NULL));
int main(){
	freopen("test.in","w",stdout);
	ll n=100000;
	cout<<n<<endl;

	while(n--)
		printf("%lld %lld\n",myrand()%MX+1,myrand()%MX+1);


	return 0;
}
