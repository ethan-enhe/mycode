#include<bits/stdc++.h>
using namespace std;
const int MXN=1e6+5;
string arr[MXN],brr[MXN];
int cnta[7][3],cntb[7][3];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		char x=arr[i][arr[i].size()-1];
		int tmp;
		if(x=='M')tmp=0;
		else if(x=='S')tmp=1;
		else tmp=2;
		cnta[arr[i].size()][tmp]++;
	}
	for(int i=1;i<=n;i++){
		cin>>brr[i];
		char x=brr[i][brr[i].size()-1];
		int tmp;
		if(x=='M')tmp=0;
		else if(x=='S')tmp=1;
		else tmp=2;
		cntb[brr[i].size()][tmp]++;
	}
	for(int i=1;i<=4;i++)
		for(int j=0;j<3;j++)
			n-=min(cnta[i][j],cntb[i][j]);
	cout<<n;

	return 0;
}
