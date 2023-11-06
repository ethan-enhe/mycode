#include<bits/stdc++.h>
using namespace std;
const int MXN=1e6+5;
const int DIG=30;
int t[MXN*DIG][2],cnt[MXN*DIG];
int nodec=1;
inline void ins(int x){
	int p=1,d=DIG;
	cnt[p]++;
	for(;~d;d--){
		bool f=(x>>d)&1;
		if(!t[p][f])t[p][f]=++nodec;
		cnt[p=t[p][f]]++;
	}
}
inline int grank(int x){
	int rk=0,p=1,d=DIG;
	for(;~d && p;d--)
		if((x>>d)&1)rk+=cnt[t[p][0]],p=t[p][1];
		else p=t[p][0];
	return rk+cnt[p];
}
inline int delrk(int rk){
	int res=0,p=1,d=DIG;
	cnt[p]--;
	for(;~d;d--){
		int tmp=cnt[t[p][0]];
		if(tmp<rk)rk-=tmp,res|=1<<d,p=t[p][1];
		else p=t[p][0];
		cnt[p]--;
	}
	return res;
}

int main(){
	ins(1);
	ins(3);
	ins(3);
	ins(4);
	ins(5);
	//scanf("%d",&n);
	return 0;
}
