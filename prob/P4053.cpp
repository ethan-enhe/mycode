#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
ll n,tot;pi arr[150005];
priority_queue<ll> q;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&arr[i].se,&arr[i].fi);
	sort(arr+1,arr+1+n);
	tot=0;
	for(int i=1;i<=n;i++){
		if(tot+arr[i].se<=arr[i].fi){
			tot+=arr[i].se;
			q.push(arr[i].se);
		}
		else if(!q.empty() && q.top()>arr[i].se){
			tot+=arr[i].se-q.top();
			q.pop();q.push(arr[i].se);
		}
	}
	printf("%lld",(ll)q.size());
	return 0;
}
