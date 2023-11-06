# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 5005;
int T, n;
int a[MAXN], b[MAXN];
int mx[MAXN], mi[MAXN];
int d[MAXN][MAXN], f[MAXN][MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			b[i] = a[i];
		}
		for (int l = 1; l <= n; l++){
			for (int r = l; r <= n; r++) d[l][r] = r;
		}
		for (int r = 1; r <= n; r++){
			mx[r] = mi[r] = a[r];
			for (int l = r - 1; l >= 1; l--){
				mx[l] = max(mx[l + 1], a[l]);
				mi[l] = min(mi[l + 1], a[l]);
			}
			int pt = r;
			while (pt + 1 <= n && a[pt + 1] > mx[1]) pt++;
			for (int l = 1; l <= r; l++){
				while (pt + 1 <= n && a[pt + 1] > mx[l]) pt++;
				d[l][pt] = min(d[l][pt], r);
			}
		}
		for (int l = 1; l <= n; l++){
			for (int r = n; r >= l; r--){
				if (r + 1 <= n) d[l][r] = min(d[l][r], d[l][r + 1]);
			}
		}
		ll ans = 0;
		for (int l = n; l >= 1; l--){
			for (int r = l; r <= n; r++){
				f[l][r] = d[l][r] - l + f[d[l][r] + 1][r];
				ans += f[l][r];
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
