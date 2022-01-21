#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef pair<int,int> pi;
const int go[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
const int MXN=5e5+5;
int n,cnt;
bool ans[MXN];
int id[MXN][5];
pi arr[MXN],pool[MXN*10];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&arr[i].fi,&arr[i].se);
		pool[++cnt]=arr[i];
		for(int j=0;j<8;j++)
			pool[++cnt]=mp(arr[i].fi+go[j][0],arr[i].se+go[j][1]);
	}
	sort(pool+1,pool+1+cnt);
	cnt=unique(pool+1,pool+1+cnt)-pool-1;
	return 0;
}
