#include<bits/stdc++.h>
using namespace std;
const int MX=1000000000;
int main(){
	int n=10000;
	cout<<n<<endl;;
	for(int i=1;i<=n;i++)
		cout<<rand()%MX<<" "<<rand()%MX<<endl;
	return 0;
}
