#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5+5;
int n,m;
bool f[MXN],op[MXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			f[i]=op[i]=0;
		}
		for(int i=1;i<=m;i++){
			int a;
			cin>>a;
			if(op[a]){
				cout<<"the lights are already on!"<<'\n';
			}
			else{
				int cnt=0;
				op[a]=1;
				for(int j=a;j<=n;j+=a){
					if(!f[j]){
						f[j]=1;
						++cnt;
					}
				}
				if(!cnt)
					cout<<"the lights are already on!"<<'\n';
				else cout<<cnt<<'\n';
			}
		}
	}
	
	return 0;
}

