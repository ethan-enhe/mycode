#include<bits/stdc++.h>
using namespace std;
const int MXN=305;
char mp[MXN][MXN];
int main(){
	srand(time(0));
	int n=10,m=10,k=15;
	cout<<n<<" "<<m<<" "<<k<<endl;
	memset(mp,'.',sizeof(mp));
	while(k--){
		int tx,ty;
		do tx=rand()%n+1,ty=rand()%m+1;while(mp[tx][ty]!='.');
		mp[tx][ty]='S';
		do tx=rand()%n+1,ty=rand()%m+1;while(mp[tx][ty]!='.');
		mp[tx][ty]='T';
	}
	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=m;j++)
			putchar(mp[i][j]);
	return 0;
}
