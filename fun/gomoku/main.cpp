#include<bits/stdc++.h>
using namespace std;
const int SZ=15;

//Basic
struct pr{
	int x,y;
	inline pr(int x=0,int y=0):x(x),y(y){}
	inline bool operator == (const pr &b)const{return x==b.x && y==b.y;}
	inline pr operator + (const pr &b)const{return pr(x+b.x,y+b.y);}
	inline pr operator - (const pr &b)const{return pr(x-b.x,y-b.y);}
	inline pr operator * (const int &b)const{return pr(x*b,y*b);}
	inline void prt(){printf("(%d,%d) ",x,y);}
};
const pr GO[8]={pr(1,0),pr(-1,0),pr(0,1),pr(0,-1),pr(1,1),pr(1,-1),pr(-1,1),pr(-1,-1)};

inline bool inbrd(pr co){return co.x>0 && co.y>0 && co.x<=SZ && co.y<=SZ;}
struct board{
	//0=空，-1=白，1=黑
	//turn表示下一子该谁下
	int arr[SZ+1][SZ+1],turn;
	inline board(){turn=1;memset(arr,0,sizeof(arr));}

	//传坐标返回是否成功
	inline bool put(pr co){
		if(!inbrd(co) || arr[co.x][co.y])return 0;
		arr[co.x][co.y]=turn;turn=-turn;
		return 1;
	}
	inline void prt(){
		printf("Turn: %s\n",(turn==1?"Black":"White"));
		for(int i=1;i<=SZ;i++,putchar('\n'))
			for(int j=1;j<=SZ;j++)
				printf(arr[i][j]?(arr[i][j]==1?"x ":"o "):". ");
	}
};


//Assess
//用于维护防守点的集合，暴力实现
struct myset{
	bool inf;
	vector<pr> st;
	inline myset(){inf=0;}
	inline void setinf(){
		st.clear();
		inf=1;
	}
	inline int size()return st.size();}
	inline bool has(pr va)const{
		if(inf)return 1;
		for(pr x:st)if(va==x)return 1;
		return 0;
	}
	inline void insert(pr x){if(!has(x))st.push_back(x);}
	inline myset operator & (const myset &b)const{
		if(inf)return b;
		if(b.inf)return *this;
		myset res;
		for(pr x:st)if(b.has(x))res.st.push_back(x);
		return res;
	}
	inline void prt(){
		if(inf)printf("inf\n");
		else{
			for(pr x:st)x.prt();
			putchar('\n');
		}
	}
};
//棋形匹配
struct pat{
	int match,len;
	vector<int> arr,pre,def;
	inline int find(int ind,int va){
		while(~ind && arr[ind+1]!=va)
			ind=pre[ind];
		return ind;
	}
	inline void reset(){match=0;}
	inline bool insert(int va){return (match=find(match,va)+1)==len;}
	inline pat(vector<int> tarr,vector<int> tdef){
		def=tdef;
		len=tarr.size();
		arr.push_back(0);
		pre.push_back(-1);
		for(int i=0;i<len;i++){
			arr.push_back(tarr[i]);
			pre.push_back(find(pre[i],tarr[i])+1);
		}
	}
};

//棋盘数据
struct state{
	myset def4,def3;
	int r3,a2,r2;
	inline state(){
		def4.setinf();
		def3.setinf();
		r3=a2=r2=0;
	}
};

//防守点数&地势得分






int main(){

	return 0;
}
