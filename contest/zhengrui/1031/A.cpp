#include <bits/stdc++.h>
#define va(a,b) a[b.x][b.y]
using namespace std;
typedef long long ll;
const ll MXN=35;
ll n,m,k;
bool rabbit[MXN][MXN];
struct coor{
	ll x,y;
	inline coor operator + (const coor &b)const{return {x+b.x,y+b.y};}
};
inline void simula
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	while(k--){
		coor tmp;
		scanf("%lld%lld",&tmp.x,&tmp.y);
		va(rabbit,tmp)=1;
	}
	return 0;
}
