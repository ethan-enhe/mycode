#include<bits/stdc++.h>
using namespace std;
int main(){
	int tp;
	scanf("%d",&tp);
	if(tp==1){
		puts("I");
		puts("I");
		puts("+ 1 2");
		puts("+ 3 3");
		puts("- 4");
		puts("O 5");
	}
	else if(tp==2){
		puts("I");
		puts("< 1 4");
		puts("+ 1 2");
		puts("- 3");
		puts("S 4");
		puts("O 5");
	}
	else if(tp==3){
		puts("I");
		puts("< 1 500");
		puts("S 2");
		puts("C 3 -0.5");
		puts("+ 4 4");
		puts("O 5");
	}
	else if(tp==4){
		puts("I");
		puts("< 1 500");
		puts("S 2");
		puts("C 3 -0.5");
		puts("+ 4 4");
		puts("* 1 5");
		puts("O 6");
	}
	else if(tp==5){
		puts("I");
		for(int i=1;i<32;i++){
			puts("I");
			printf("+ %d %d\n",i*3-2,i*3-2);
			printf("+ %d %d\n",i*3,i*3-1);
		}
		puts("O 94");
	}
	else if(tp==6){
		puts("I");
		for(int i=31;i;i--){
			printf("> %d %d\n",,i);
			//-1
			//左500
			//S
			//-0.5
			//*2;

		}
	}
	return 0;
}
