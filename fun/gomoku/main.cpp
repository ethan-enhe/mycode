#include<bits/stdc++.h>
using namespace std;
const int SZ=15;
struct pr{
	int x,y;
	pr(int x=0,int y=0):x(x),y(y){}
};


bool inbrd(pr co){return co.x>0 && co.y>0 && co.x<=SZ && co.y<=SZ;}
struct board{
	int arr[SZ+1][SZ+1],turn;
	board(){memset(arr,-1,sizeof(arr));turn=0;}

#define va(a) arr[a.x][a.y]
	bool put(pr co){
		if(!inbrd(co) || ~va(co))return 0;
		return va(co)=(++turn)&1,1;
	}
	void prt(){
		for(int i=1;i<=SZ;i++,putchar('\n'))
			for(int j=1;j<=SZ;j++)
				putchar(~arr[i][j]?(arr[i][j]?'X':'O'):'.');
	}
};
int main(){
	return 0;
}
