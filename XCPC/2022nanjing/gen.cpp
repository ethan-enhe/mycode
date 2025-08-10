
# include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
# define fi first
# define se second
const int MAXN = 400051;
mt19937 mrd(time(0));
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	freopen("j.in", "w", stdout);
	cout << 10 << '\n';
	for (int i = 1; i <= 9; i++){
		int n = 100000;
		cout << n << '\n';
		for (int j = 1; j <= n; j++){
			cout << int(mrd() % n) - (n / 2) << ' ';
		}
		cout << '\n';
	}
	int n = 100000;
	cout << n << '\n';
	for (int j = 1; j <= n; j++){
		cout << j << ' ';
	}
	cout << '\n';
	return 0;
}
