#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int N = 5005;
const long long mod = 1ll << 32;
int n, a[N], mx;
long long ans, S[N][N];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++ ) {
		scanf("%lld", &a[i]);
		mx = max(mx, a[i]);
	}
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 1; j <= n; j ++ )
			if (i != j)
				S[i][a[j]] += a[j] / a[i];
		for (int j = 1; j <= 5000; j ++ )
			S[i][j] += S[i][j - 1];
	}
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			if (a[i] > a[j] && i != j) {
				int b = a[i], c = a[j];
				for (int s = 1; s <= mx / c; s ++ ) {
					/*
					s<=a/c<s+1
					c*s<=a<(s+1)*c
					c*s<=a<=(s+1)*c-1
					*/
					int L = c*s, R = (s+1) * c - 1;
					//>=L&&<=R&&>=a[i]
					//>=max(L,a[i])&&<=R
					L = max(L, a[i]+1);
					if (L <= R) {
						// printf("%d %d %lld %d %d %d\n", a[i], a[j], s, 1ll * (S[i][R] - S[i][L - 1]) * (b / c) * s, L, R);
						(ans += 1ll * (S[i][R] - S[i][L - 1]) * (b / c) * s) %= mod;
                        if(S[i][R] - S[i][L - 1]<0)cout<<i<<" "<<L<<" "<<R<<endl;
					}
				}
			}
	printf("%lld\n", ans);
	return 0;
}
