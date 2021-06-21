#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
//{{{ def
typedef pair<int,int> pi;
const int MXN=5e5+5;
int n,arr[MXN],p1[MXN],p2[MXN];
//}}}
//{{{ func
pi q[MXN];int ql,qr;
inline void solve(int *p,int (*f)(int,int)){
	q[ql=qr=1]=mp(1,1);
	for(int i=1;i<=n;i++){
		while(ql<qr && q[ql+1].se<=i)ql++;
		p[i]=f(q[ql].fi,i);

		while(ql<=qr && f(i,q[qr].se)>=f(q[qr].fi,q[qr].se))qr--;
		int l=q[qr].fi,r=n;
		while(l<r){
			int mid=(l+r)>>1;
		}

	}
}
inline int cost1(int x,int y){return arr[y]-arr[x]+ceil(sqrt(y-x));}
inline int cost2(int x,int y){return arr[x]-arr[y]+ceil(sqrt(y-x));}
//}}}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",arr+i);
	solve(p1,cost1);
	reverse(arr+1,arr+1+n);
	solve(p2,cost2);
	for(int i=1;i<=n;i++)printf("%d\n",max(p1[i],p2[i]));
	return 0;
