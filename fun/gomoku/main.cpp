#include<bits/stdc++.h>
using namespace std;
const int SZ=15;
const int GO[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

struct pr{
	int x,y;
	pr(int x=0,int y=0):x(x),y(y){}
};


inline bool inbrd(pr co){return co.x>0 && co.y>0 && co.x<=SZ && co.y<=SZ;}
struct board{
	//0=空，-1=白，1=黑
	//turn表示下一子该谁下
	int arr[SZ+1][SZ+1],turn;
	board(){turn=1;memset(arr,0,sizeof(arr));}

	//传坐标返回是否成功
	bool put(pr co){
		if(!inbrd(co) || arr[co.x][co.y])return 0;
		arr[co.x][co.y]=turn;turn=-turn;
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
	double five,afour,rfour,athree,rthree,atwo,rtwo;
	board_sta(){five=afour=rfour=athree=rthree=atwo=rtwo=0;}
};

inline bool chkfive(int arr[SZ+1][SZ+1],pr co,int turn){
    if(arr[co.x][co.y]!=turn)return 0;
    for(int i=0;i<8;i++){
        bool f=1;pr tco=co;
        for(int j=1;j<=4;j++){
            tco.x+=GO[i][0],tco.y+=GO[i][1];
            if(arr[tco.x][tco.y]!=turn){
                f=0;
                break;
            }
        }
        if(f)return 1;
    }
    return 0;
}




int main(){
	return 0;
}
