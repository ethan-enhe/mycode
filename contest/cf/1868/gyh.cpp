# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
# define fi first
# define se second
const int MAXN = 1000051;
const int P = 998244353;
const ll INV2 = (P + 1) / 2;
ll pwr(ll x, ll y){
	x %= P;
	y = (y % (P - 1) + (P - 1)) % (P - 1);
	ll ans = 1;
	while (y){
		if (y & 1) ans = ans * x % P;
		x = x * x % P;
		y >>= 1;
	}
	return ans;
}
int T;
ll n, m;
ll f0[100], f1[100];
ll g0[100], g1[100];
ll wrk(ll p){
	p = (1 - p) % P;
	ll ans = 0;
	f1[0] = f0[0] = p;
	g1[0] = g0[0] = p;
	ll hgt = 0;
	while ((1ll << (hgt + 1)) <= n) hgt++;
	ans = 1ll * (n - (1ll << hgt) + 1) % P * f1[0] % P;
	// cerr << "ans00 " << ans << '\n';
	// cerr << "hgt " << hgt << '\n';
	for (int i = 1; i <= hgt; i++){
		if ((n >> (i - 1)) & 1){
			f1[i] = p * (g0[i - 1] + 1) % P * (g1[i - 1] + 1) % P;
			g1[i] = p * (1 + g0[i - 1] + g1[i - 1]) % P;
		} else {
			if (i == 1){
				f1[i] = p * (g1[i - 1] + 1) % P * (0 + 1) % P;
				g1[i] = p * (1 + g1[i - 1] + 0) % P;
			} else {
				f1[i] = p * (g1[i - 1] + 1) % P * (g0[i - 2] + 1) % P;
				g1[i] = p * (1 + g1[i - 1] + g0[i - 2]) % P;
			}
		}
		f0[i] = p * (g0[i - 1] + 1) % P * (g0[i - 1] + 1) % P;
		g0[i] = p * (1 + g0[i - 1] + g0[i - 1]) % P;
		ll tol = (1ll << (hgt - i));
		ll nm1 = (n >> i) - (1ll << (hgt - i));
		ll nm2 = tol - nm1 - 1;
		nm1 %= P;
		nm2 %= P;
		ans = (ans + nm1 * f0[i] + f1[i] + nm2 * f0[i - 1]) % P;
	}
	// cerr << "ans0 " << ans << '\n';
	ans = (n % P * ((n + 1) % P) % P * INV2 % P - ans) % P;
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n >> m;
		ll ans = 0;
		ll ivm = pwr(m, -1);
		for (int i = 1; i <= m; i++){
			ans = (ans + wrk((m - i + 1) * ivm)) % P;
		}
		ans = ans * pwr(m, n) % P;
		cout << (ans % P + P) % P << '\n';
	}
	return 0;
}
