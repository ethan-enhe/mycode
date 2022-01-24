#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MXN = 1e6 + 5;
ll n, m, k;
struct que {
	ll a, b, p, q, ans;
} arr[MXN];
struct tp{
	ll x,y,z;
	bool operator<(const tp &b)const{
		if(x==b.x){
			if(y==b.y)
				return z<b.z;
			return y<b.y;
		}
		return z<b.z;
	}
};
ll f[MXN];

ll gcd(ll x, ll y) {
	return y?gcd(y,x%y):x;
}
void exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0)
		x = 1, y = 0;
	else
		exgcd(b, a % b, y, x), y -= x * (a / b);
}
ll inv(ll a, ll p) {
	ll x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}
map<tp, ll> ind;
vector<ll> ask[MXN];
int main(int argc, char *argv[]) {
	scanf("%lld%lld", &n, &m);
	for (ll i = 1; i <= n; i++) {
		ll a, b, g, p, q;
		scanf("%lld%lld", &a, &b);

		if (!a)
			arr[i].ans = 0;
		else if (!b)
			arr[i].ans = 1;
		else {
			g = gcd(gcd(a, b), m);
			a /= g, b /= g;
			p = gcd(a, m / g), q = gcd(b, m / g);
			arr[i] = {a, b, p, q};
			ask[g].push_back(i);
		}
	}
	f[1] = 1;
	for (k = 2;; k++) {
		f[k] = (f[k - 2] + f[k - 1]) % m;
		if (f[k] == 1 && f[k - 1] == 0)
			break;
	}
	for (ll g = 1; g <= m; g++)
		if (ask[g].size()) {
			ind.clear();
			ll tm = m / g;
			for (ll i = 1; i <= k; i++)
				if (f[i] && f[i - 1]) {
					ll p = gcd(f[i], m / g), q = gcd(f[i - 1], m / g);
					ll cm = tm / p / q;
					ll tmp = (cm - f[i] / p * inv(f[i - 1] / q, cm) % cm) % cm;
					if (ind.find({p, q, tmp}) == ind.end())
						ind[{p, q, tmp}] = i;
				}
			for (ll &i : ask[g]) {
				ll cm = tm / arr[i].p / arr[i].q;
				auto it = ind.find(
					{arr[i].p, arr[i].q,
					 arr[i].a / arr[i].p * inv(arr[i].b / arr[i].q, cm) % cm});
				arr[i].ans = it == ind.end() ? -1 : it->second;
			}
		}
	for (ll i = 1; i <= n; i++)
		printf("%lld\n", arr[i].ans);

	return 0;
}
