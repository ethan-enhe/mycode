
#include <cstdio>
#include <algorithm>
using namespace std;
int n , m , x , y , v[105][105][2];
short f[105][105][105][105];
signed main() {
	scanf("%d %d" , &n , &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char s = getchar();
			while(s != 'o' && s != '.' && s != 'E') s = getchar();
			if(s == 'E') x = i , y = j;
			else if(s == 'o') {
				v[i][j][0] = v[i - 1][j][0] + 1;
				v[i][j][1] = v[i][j - 1][1] + 1;
			}
			else {
				v[i][j][0] = v[i - 1][j][0];
				v[i][j][1] = v[i][j - 1][1];
			}
		}
	}
	int ans = 0;
	for (int l = 0; l <= y - 1; ++l) {
		for (int r = 0; r <= m - y; ++r) {
			for (int u = 0; u <= x - 1; ++u) {
				for (int d = 0; d <= n - x; ++d) {
					ans = max(ans , (int)f[l][r][u][d]);
					if(l + r < y - 1) f[l + 1][r][u][d] = max((int)f[l + 1][r][u][d] , (int)f[l][r][u][d] + v[min(x + d , n - u)][y - l - 1][0] - v[max(x - u - 1 , d)][y - l - 1][0]);
					if(l + r < m - y) f[l][r + 1][u][d] = max((int)f[l][r + 1][u][d] , (int)f[l][r][u][d] + v[min(x + d , n - u)][y + r + 1][0] - v[max(x - u - 1 , d)][y + r + 1][0]);
					if(u + d < x - 1) f[l][r][u + 1][d] = max((int)f[l][r][u + 1][d] , (int)f[l][r][u][d] + v[x - u - 1][min(y + r , m - l)][1] - v[x - u - 1][max(y - l - 1 , r)][1]);
					if(u + d < n - x) f[l][r][u][d + 1] = max((int)f[l][r][u][d + 1] , (int)f[l][r][u][d] + v[x + d + 1][min(y + r , m - l)][1] - v[x + d + 1][max(y - l - 1 , r)][1]);
				}
			}
		}
	}
	printf("%d" , ans);
	return 0;
}
