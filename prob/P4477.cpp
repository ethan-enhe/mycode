#include<bits/stdc++.h>
using namespace std;
const int MXN=2e5;
const int MXM=5.3e4;
const int SQRT=300;

struct que{
	int l,r,i;
	inline que(int l=0,int r=0,int i=0):l(l),r(r),i(i){}
	inline bool operator < (const que &b)const{return r<b.r;}
};
vector<que> ask[SQRT];


int n,m,z,q;
int brr[MXM];
int ans[MXM];


stack<int> ml,mr;
set<int> pre;
inline void add(int x,stack<int> &st){
	set<int>::iterator it=pre.lower_bound(brr[x]);
	if(it!=pre.end()){
		st.push(*it);
		pre.erase(it);
	}
}
inline void undo(stack<int> &st){
	while(!st.empty()){
		pre.insert(st.top());
		st.pop();
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&z);
	for(int i=1,tmp;i<=n;i++){
		scanf("%d",&tmp);
		if(z>tmp)pre.insert(z-tmp);
	}
	for(int i=1;i<=m;i++)scanf("%d",brr+i);
	scanf("%d",&q);
	for(int i=1,tl,tr;i<=q;i++){
		scanf("%d%d",&tl,&tr);
		ask[tl/SQRT].push_back(que(tl,tr,i));
	}
	for(int i=0,br=SQRT-1;i<SQRT;i++,br+=SQRT){
		int ir=br;
		sort(ask[i].begin(),ask[i].end());
		for(size_t j=0;j<ask[i].size();j++){
			while(ir<ask[i][j].r)add(++ir,mr);
			while(ask[i][j].l<=min(br,ask[i][j].r))add(ask[i][j].l++,ml);
			ans[ask[i][j].i]=ml.size()+mr.size();
			undo(ml);
		}
		undo(mr);
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);

	return 0;
}
