#include<bits/stdc++.h>
using namespace std;
const int SZ=1<<24;
const int DSZ=1.3e7;
template<class T>
struct hmap{
	typedef unsigned long long ull;
	int head[SZ],nx[DSZ],cnt;ull h[DSZ];T data[DSZ];
	inline hmap(){memset(head,0,sizeof(head)),cnt=0;}
	inline T &operator [] (const ull &x){
		int ind=(x^(x>>23)^(x>>46))&(SZ-1);
		for(int i=head[ind];i;i=nx[i])
			if(h[i]==x)
				return data[i];
		return nx[++cnt]=head[ind],head[ind]=cnt,h[cnt]=x,data[cnt];
	}
};
int main(){

	return 0;
}
