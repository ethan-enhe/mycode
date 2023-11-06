#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
const int MXN=160,MXS=1e6+5,MXT=80;
int n,nodec;
char str[MXS],arr[MXN][MXT];
struct node{
	int fail,lab,cnt,son[26];
	inline void init(){
		fail=lab=cnt=0;
		memset(son,0,sizeof(son));
	}
}t[MXN*MXT];
inline int nnode(){return t[++nodec].init(),nodec;}
inline void ins(char *tmp,int id){
	int l=strlen(tmp+1),p=0;
	for(int i=1;i<=l;i++){
		int va=tmp[i]-'a';
		if(!t[p].son[va])t[p].son[va]=nnode();
		p=t[p].son[va];
	}
	t[p].lab=id;
}
queue<int> q;
inline void build(){
	for(int i=0;i<26;i++)
		if(t[0].son[i])
			q.push(t[0].son[i]);
	while(!q.empty()){
		int p=q.front();q.pop();
		for(int i=0;i<26;i++){
			int &nx=t[p].son[i];
			if(nx){
				t[nx].fail=t[t[p].fail].son[i];
				q.push(nx);
			}
			else nx=t[t[p].fail].son[i];
		}
	}
}
int mx=0;
vector<int> ans,g[MXN*MXT];
inline void dfs(int p){
	for(int nx:g[p]){
		dfs(nx);
		t[p].cnt+=t[nx].cnt;
	}
	if(t[p].lab){
		if(t[p].cnt>mx){
			mx=t[p].cnt;
			ans.clear();
			ans.push_back(t[p].lab);
		}
		else if(t[p].cnt==mx)
			ans.push_back(t[p].lab);
	}
}
int main(){
	while(1){
		ans.clear();
		t[nodec=0].init();
		mx=0;
		scanf("%d",&n);
		if(!n)break;
		for(int i=1;i<=n;i++){
			scanf("%s",arr[i]+1);
			ins(arr[i],i);
		}
		build();
		scanf("%s",str+1);
		int l=strlen(str+1),p=0;
		for(int i=1;i<=l;i++)
			t[p=t[p].son[str[i]-'a']].cnt++;
		for(int i=1;i<=nodec;i++)g[t[i].fail].push_back(i);
		dfs(0);
		printf("%d\n",mx);
		sort(ans.begin(),ans.end());
		for(int i:ans)
			printf("%s\n",arr[i]+1);
		for(int i=0;i<=nodec;i++)g[i].clear();
	}
	return 0;
}
