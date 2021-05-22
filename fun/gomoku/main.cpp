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
		printf("  ");
		for(int j=1;j<=SZ;j++)
			printf("%3d",j);
		for(int i=1;i<=SZ;i++){
			putchar('\n');
			printf("%2d ",i);
			for(int j=1;j<=SZ;j++)
				printf(arr[i][j]?(arr[i][j]==1?" ● ":" ○ "):" . ");
		}
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
	inline int size(){return st.size();}
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
	inline myset operator | (const myset &b)const{
		if(inf)return *this;
		if(b.inf)return b;
		myset res;
		for(pr x:st)res.st.push_back(x);
		for(pr x:b.st)res.st.push_back(x);
		return res;
	}
};
//棋形匹配
struct pat{
	int match,len;
	vector<int> arr,pre,def,att;
	inline int find(int ind,int va){
		while(~ind && arr[ind+1]!=va)
			ind=pre[ind];
		return ind;
	}
	inline void reset(){match=0;}
	inline bool insert(int va){return (match=find(match,va)+1)==len;}
	inline pat(vector<int> tarr,vector<int> tatt){
		att=tatt;
		len=tarr.size();
		arr.push_back(0);
		pre.push_back(-1);
		for(int i=0;i<len;i++){
			if(!tarr[i])def.push_back(i+1);
			arr.push_back(tarr[i]);
			pre.push_back(find(pre[i],tarr[i])+1);
		}
	}
};



//棋盘数据
struct state{
	//att表示冲的位置
	//def表示防守点
	myset att5,att4,att3,def4,def3;
	inline state(){
		def4.setinf();
		def3.setinf();
	}
};

//成五点数
vector<pat> ar4={
	pat({1,1,1,1,0},{5}),
	pat({1,1,1,0,1},{4}),
	pat({1,1,0,1,1},{3}),
	pat({1,0,1,1,1},{2}),
	pat({0,1,1,1,1},{1})
};
//3->活4
vector<pat> a3={
	pat({0,1,1,1,0,0},{5}),
	pat({0,0,1,1,1,0},{2}),
	pat({0,1,1,0,1,0},{4}),
	pat({0,1,0,1,1,0},{3})
};

//3->冲4
vector<pat> r3={
	pat({1,1,1,0,0},{4,5}),
	pat({1,1,0,1,0},{3,5}),
	pat({1,0,1,1,0},{2,5}),
	pat({0,1,1,1,0},{1,5}),
	pat({1,1,0,0,1},{3,4}),
	pat({1,0,1,0,1},{2,4}),
	pat({0,1,1,0,1},{1,4}),
	pat({1,0,0,1,1},{2,3}),
	pat({0,1,0,1,1},{1,3}),
	pat({0,0,1,1,1},{1,2})
};

//2->活3
vector<pat> a2={
	pat({0,1,1,0,0,0},{4,5}),
	pat({0,1,0,1,0,0},{3,5}),
	pat({0,1,0,0,1,0},{3,4}),
	pat({0,0,1,1,0,0},{2,5}),
	pat({0,0,1,0,1,0},{2,4}),
	pat({0,0,0,1,1,0},{2,3})
};

state cal(board cbd,int side){
	state res;
	pr move=pr(0,1);
	for(int i=1;i<=SZ;i++){
		for(pat &p:ar4)p.reset();
		for(pat &p:a3) p.reset();
		for(pat &p:r3) p.reset();
		for(pat &p:a2) p.reset();
		for(pr curpos(i,1);inbrd(curpos);curpos=curpos+move){
			int cur=cbd.arr[curpos.x][curpos.y]*side;
			for(pat &p:ar4)
				if(p.insert(cur)){
					for(int ind:p.att)
						res.att5.insert(curpos+move*(ind-p.len));
					for(int ind:p.def)
						res.def4.insert(curpos+move*(ind-p.len));
				}
			for(pat &p:a3)
				if(p.insert(cur)){
					for(int ind:p.att)
						res.att4.insert(curpos+move*(ind-p.len));
					for(int ind:p.def)
						res.def3.insert(curpos+move*(ind-p.len));
				}
			for(pat &p:r3)
				if(p.insert(cur))
					for(int ind:p.att)
						res.att4.insert(curpos+move*(ind-p.len));

			for(pat &p:a2)
				if(p.insert(cur))
					for(int ind:p.att)
						res.att3.insert(curpos+move*(ind-p.len));
		}
	}

	return res;

}






int main(){
	board tmp;
	tmp.put(pr(8,8));
	tmp.put(pr(7,7));
	tmp.put(pr(9,7));
	tmp.put(pr(7,9));
	tmp.prt();

	

	return 0;
}
