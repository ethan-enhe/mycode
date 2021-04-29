#include<bits/stdc++.h>
using namespace std;
const int SZ=15;
struct pr{
	int x,y;
	pr(int x=0,int y=0):x(x),y(y){}
};


inline bool inbrd(pr co){return co.x>0 && co.y>0 && co.x<=SZ && co.y<=SZ;}

#define va(a) arr[a.x][a.y]
struct board{
	//0=空，-1=白，1=黑
	//turn表示下一子该谁下
	int arr[SZ+1][SZ+1],turn;
	board(){memset(arr,0,sizeof(arr));turn=1;}

	//传坐标返回是否成功
	bool put(pr co){
		if(!inbrd(co) || va(co))return 0;
		va(co)=turn;turn=-turn;
		return 1;
	}
	void prt(){
		printf("Turn: %s\n",(turn==1?"Black":"White"));
		for(int i=1;i<=SZ;i++,putchar('\n'))
			for(int j=1;j<=SZ;j++)
				printf(arr[i][j]?(arr[i][j]==1?"X ":"O "):". ");
	}
};



struct board_sta{
	//a前缀表示活，r前缀表示眠/冲
	int five,afour,rfour,athree,rthree,atwo,rtwo;
	board_sta(){five=afour=rfour=athree=rthree=atwo=rtwo=0;}
};

inline bool match(){
}

int main(){

	return 0;
}
