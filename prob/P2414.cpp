#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef pair<int,int> pi;
const int MXN=1e5+5;

char str[MXN];int q;
vector<int> e[MXN];
vector<pi> que[MXN];
int t[MXN][26],fail[MXN],endp[MXN];

int ind,strc,nodec;
inline void bldtrie(int p){
	while(str[++ind]){
		if(str[ind]=='P')endp[++strc]=p;
		else if(str[ind]=='B')return;
		else{
			int tmp=str[ind]-'a';
			if(!t[p][tmp])t[p][tmp]=++nodec;
			bldtrie(t[p][tmp]);
		}
	}
}
inline void bldfail(){
	queue<int> q;
	for(int i=0;i<26;i++)
		if(t[0][i])
			q.push(t[0][i]);
	while(!q.empty()){
		int p=q.front();q.pop();
		for(int i=0;i<26;i++){
			int &nx=t[p][i];
			if(nx){
				fail[nx]=t[fail[p]][i];
				q.push(nx);
			}
			else nx=t[fail[p]][i];
		}
	}
}


int main(){
	scanf("%s%d",str+1,&q);
	bldtrie(0);
	for(int i=1,tx,ty;i<=q;i++){
		scanf("%d%d",&tx,&ty);
		que[endp[ty]].pb(mp(tx,i));
	}
	bldfail();
	return 0;
}
