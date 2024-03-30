#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 5000 + 3;
int n, m = 5000, A[MAXN]; bool C[MAXN];
unsigned ans = 0, D[MAXN][MAXN];
int qread(){
    int w=1,c,ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int main(){
    n = qread();
    up(1, n, i) A[i] = qread(), C[A[i]] = true;
    up(1, m, c) if(C[c]){
        up(1, m, i){
            int a1 = c * i, a2 = min(c * (i + 1) - 1, m);
            if(a1 > a2) break;
            up(1, m, j){
                int b1 = c * j, b2 = min(c * (j + 1) - 1, m);
                if(b1 > b2) break;
                a1 = max(a1, c + 1);
                b1 = max(b1, c + 1);
                D[    a1][    b1] += i * j;
                D[    a1][b2 + 1] -= i * j;
                D[a2 + 1][    b1] -= i * j;
                D[a2 + 1][b2 + 1] += i * j;
            }
        }
    }
    up(1, m, i) up(1, m, j){
        D[i][j] += D[i][j - 1];
    }
    up(1, m, i) up(1, m, j){
        D[i][j] += D[i - 1][j];
    }
    up(1, m, a) up(1, m, b) if(a > b){
        if(C[a] && C[b])
            ans += (a / b) * D[a][b];
    }
    printf("%u\n", ans);
    return 0;
}
