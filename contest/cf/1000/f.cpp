#include<bits/stdc++.h>
using namespace std;
const int MXN=5e5+5;
const int BLK=sqrt(MXN);
typedef int arrn[MXN];
int n,m;
arrn arr,cnt,ans;
struct q{
	int l,lbk,r,id;
	inline bool operator < (const q &b)const{return lbk==b.lbk?(lbk&1?r>b.r:r<b.r):lbk<b.lbk;}
}ask[MXN];
bool inq[MXN];
queue<int> q;
inline void mod(int x,int y){
	x=arr[x];
	cnt[x]+=y;
	if(cnt[x]==1 && !inq[x]){
		q.push(x);
		inq[x]=1;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",arr+i);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].id=i,ask[i].lbk=ask[i].l/BLK;
	}
	sort(ask+1,ask+1+m);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(r<ask[i].r)mod(++r,1);
		while(l>ask[i].l)mod(--l,1);
		while(r>ask[i].r)mod(r--,-1);
		while(l<ask[i].l)mod(l++,-1);
		while(!q.empty() && cnt[q.front()]!=1){
			inq[q.front()]=0;
			q.pop();
		}
		if(!q.empty())ans[ask[i].id]=q.front();

	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);

	return 0;
}
