//手写vector，不开O2，插入次数小时优势明显
#include<bits/stdc++.h>
using namespace std;
template<class T>
struct vec{
	T *arr;int sz,top;
	inline vec(){arr=NULL,sz=top=0;}
	inline ~vec(){free(arr);}
	inline T &operator [] (const int &x){return arr[x];}
	inline void pb(const T &x){
		if(sz==top)
			arr=(T*)realloc(arr,sizeof(T)*(top=max(top<<1,1)));
		arr[sz++]=x;
	}
};
int main(){
	return 0;
}

