#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int SZ=15;
ull hashtable[3][SZ+1][SZ+1];

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

inline bool inbrd(pr co){return co.x>0 && co.y>0 && co.x<=SZ && co.y<=SZ;}
struct board{
	//0=空，-1=白，1=黑
	//turn表示下一子该谁下
	int arr[SZ+1][SZ+1],turn;
	ull hsh;
	inline board(){
		turn=1;memset(arr,0,sizeof(arr));
		hsh=0;
		for(int i=1;i<=SZ;i++)
			for(int j=1;j<=SZ;j++)
				hsh^=hashtable[1][i][j];
	}

	//传坐标返回是否成功
	inline bool put(pr co){
		if(!inbrd(co) || arr[co.x][co.y])return 0;
		hsh=hsh^hashtable[1][co.x][co.y]^hashtable[1+turn][co.x][co.y];
		arr[co.x][co.y]=turn;turn=-turn;
		return 1;
	}
	inline bool withdraw(pr co){
		if(!inbrd(co) || !arr[co.x][co.y])return 0;
		hsh=hsh^hashtable[1][co.x][co.y]^hashtable[1-turn][co.x][co.y];
		arr[co.x][co.y]=0;turn=-turn;
		return 1;
	}
	inline void prt(){
		printf("Hash: %llu\n",hsh);
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
		putchar('\n');
	}
};


//Assess
//用于维护防守点的集合，暴力实现
struct myset{
	bool inf;
	vector<pr> st;
	inline myset(){inf=0;st.clear();}
	inline void setinf(){inf=1;st.clear();}
	inline int size(){return inf?SZ*SZ:st.size();}
	inline bool has(pr va)const{
		if(inf)return 1;
		for(pr x:st)if(va==x)return 1;
		return 0;
	}
	inline void prt(){for(pr x:st)x.prt();}
	inline void insert(pr x){st.push_back(x);}
	inline myset operator & (const myset &b)const{
		if(inf)return b;
		if(b.inf)return *this;
		myset res;
		for(pr x:st)if(b.has(x))res.st.push_back(x);
		return res;
	}
};

//棋盘数据
struct state{
	//att表示冲的位置
	//def表示防守点
	bool notcal;
	myset att5,atta4,attar4,atta3,defa3;
	inline state(){notcal=1;defa3.setinf();}
	inline void prt(){
		cout<<"\n att5:";att5.prt();
		cout<<"\n atta4:";atta4.prt();
		cout<<"\n attar4:";attar4.prt();
		cout<<"\n atta3:";atta3.prt();
		cout<<"\n defa3:";atta3.prt();
		puts("\n----");
	}
};
struct boarddata{state bst,wst;};
unordered_map<ull,boarddata> saved;

inline void matchline(const board &cbd,state &res,pr start,pr move,int side){
	int va[SZ<<1|1],cnt[SZ<<1|1],blank[SZ<<1|1],blankcnt=0,lastenemy=0;
	cnt[0]=0;
	myset tmp;
	pr curpos=start;int i=1;
	for(;inbrd(curpos);i++,curpos=curpos+move){
		va[i]=cbd.arr[curpos.x][curpos.y]*side;
		cnt[i]=cnt[i-1]+va[i];
		if(va[i]==-1){
			lastenemy=i;
			continue;
		}
		if(va[i]==0){
			if(lastenemy+6<=i && va[i-5]==0){
				//活4点
				if(cnt[i-1]-cnt[i-5]==3){
					res.atta4.insert(start+move*(blank[blankcnt]-1));
					tmp=myset();
					tmp.insert(start+move*(blank[blankcnt]-1));
					tmp.insert(curpos);
					tmp.insert(start+move*(i-6));
					res.defa3=res.defa3&tmp;
				}
				//活3点
				else if(cnt[i-1]-cnt[i-5]==2){
					res.atta3.insert(start+move*(blank[blankcnt]-1));
					res.atta3.insert(start+move*(blank[blankcnt-1]-1));
				}
			}
			blank[++blankcnt]=i;
		}
		if(lastenemy+5<=i){
			//成5点
			if(cnt[i]-cnt[i-5]==4)res.att5.insert(start+move*(blank[blankcnt]-1));
			//成4点（活四冲四都可以）
			else if(cnt[i]-cnt[i-5]==3){
				res.attar4.insert(start+move*(blank[blankcnt]-1));
				res.attar4.insert(start+move*(blank[blankcnt-1]-1));
			}
		}
	}
}


inline state cal(const board &cbd,int side){
	state &res=side==1?saved[cbd.hsh].bst:saved[cbd.hsh].wst;
	if(!res.notcal)return res;
	res.notcal=0;
	for(int i=1;i<=SZ;i++){
		matchline(cbd,res,pr(i,1),pr(0,1),side);
		matchline(cbd,res,pr(1,i),pr(1,0),side);
		matchline(cbd,res,pr(1,i),pr(1,1),side);
		matchline(cbd,res,pr(1,i),pr(1,-1),side);
		if(i>1){
			matchline(cbd,res,pr(i,1),pr(1,1),side);
			matchline(cbd,res,pr(i,SZ),pr(1,-1),side);
		}
	}
	return res;
}

//Hash
inline void hashinit(){
	srand(time(NULL));
	for(int i=0;i<3;i++)
		for(int j=1;j<=SZ;j++)
			for(int k=1;k<=SZ;k++)
				hashtable[i][j][k]=((ull)rand()<<33)^((ull)rand()<<10)^(ull)rand();
}


int main(){
	int x=clock();
	hashinit();
	board tmp;
	tmp.put(pr(8,8));
	tmp.put(pr(7,7));
	tmp.put(pr(9,7));
	tmp.put(pr(7,9));
	tmp.put(pr(9,6));
	tmp.put(pr(7,6));
	tmp.put(pr(9,8));
	tmp.put(pr(7,5));
	int res=0;
	for(int i=1;i<=2000000;i++){
		state x=cal(tmp,-1);
		res+=x.defa3.size();
	}
	state a=cal(tmp,1);
	a.prt();

	
	cout<<double(clock()-x)/CLOCKS_PER_SEC;
	

	return 0;
}
