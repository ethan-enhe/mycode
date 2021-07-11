#include <bits/stdc++.h>
using namespace std;
const int SZ=1024;

FILE *fp;
inline unsigned char x(int i,int j){return sin(i*M_PI/SZ)*SZ>=j?255:0;}
int main(){
	fp = fopen("pic.ppm","wb");
	fprintf(fp, "P6\n%d %d\n255\n", SZ, SZ);
	for(int j=0;j<SZ;j++)
		for(int i=0;i<SZ;i++)
			fprintf(fp,"%c%c%c",0,j*255/SZ,i*255/SZ);
	fclose(fp);
	return 0;
}
