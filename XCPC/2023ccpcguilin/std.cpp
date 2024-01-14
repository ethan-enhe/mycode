# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
# define fi first
# define se second
const int MAXN = 300051;
int T, n, m;
int a[MAXN], b[MAXN];
set<pii> sa;
vector<int> ans;
bool chk(){
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	ll opt = n - m;
	for (int i = 1; i <= m; i++){
		if (a[n - m + i] > b[i]) return false;
		opt -= b[i] - a[n - m + i];
	}
	if (opt < 0) return false;
	for (int i = 1; i <= n; i++) sa.insert(pii(a[i], -i));
	for (int i = 1; i <= opt; i++){
		auto it = sa.begin();
		pii val = *it;
		if (val.fi >= b[1]) return false;
		ans.push_back(val.fi);
		sa.erase(it);
		a[-val.se]++;
		// cerr << "val " << val.fi << ' ' << -val.se << '\n';
		sa.insert(pii(val.fi + 1, val.se));
		if (-val.se > n - m) opt++;
		int val2 = sa.begin()->fi;
		auto it2 = --sa.lower_bound(pii(val2, 1e9));
		if (-it2->se > n - m) return false;
		sa.erase(it2);
	}
	for (int i = 1; i <= m; i++){
		for (int j = a[n - m + i]; j < b[i]; j++) ans.push_back(j);
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= m; i++) cin >> b[i];
		if (!chk()) cout << "-1\n";
		else {
			cout << n - m << '\n';
			// for (int i : ans) cout << i << ' ';
			// cout << '\n';
		}
		sa.clear();
		ans.clear();
	}
	return 0;
}
