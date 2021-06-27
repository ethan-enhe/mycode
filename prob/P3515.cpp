#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
//{{{ def
typedef pair<int,int> pi;
const int MXN=5e5+5;
int n,arr[MXN];
double p1[MXN],p2[MXN];
//}}}
//{{{ func
pi q[MXN];int ql,qr;
inline double f(int i,int j){return sqrt(i-j)+arr[j]-arr[i];}
inline void solve(double *p){
	ql=1,qr=0;
	for(int i=1;i<=n;i++){
		while(ql<=qr && f(max(q[qr].se,i),i)>=f(max(q[qr].se,i),q[qr].fi))qr--;
		if(ql>qr)q[++qr]=mp(i,1);
		else{
			int l=max(i,q[qr].fi),r=n+1;
			while(l<r){
				int mid=(l+r)>>1;
				f(mid,i)>=f(mid,q[qr].fi)?r=mid:l=mid+1;
			}
			q[++qr]=mp(i,l);
		}
		while(ql<qr && q[ql+1].se<=i)ql++;
		p[i]=f(i,q[ql].fi);
	}
}
//}}}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",arr+i);
	solve(p1);
	reverse(arr+1,arr+1+n);
	solve(p2);
	for(int i=1;i<=n;i++)
		printf("%d\n",(int)ceil(max(p1[i],p2[n-i+1])));
	return 0;
}
