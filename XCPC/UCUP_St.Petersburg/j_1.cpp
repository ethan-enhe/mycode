# include <bits/stdc++.h>
using namespace std;
mt19937 mrd(time(0));
int random(int l, int r){
	return mrd() % (r - l + 1) + l;
}
int lim = 1e9;
int n = 50;
int b[105], c[105];
void gen(int a[]){
	for (int i = 1; i <= n - 1; i++){
		a[i] = random(0, lim);
	}
	a[n] = lim;
	sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
	sort(a + 1, a + n + 1);
	int s = 0;
	for (int i = 1; i <= n; i++){
		s += a[i];
		cerr << i << ' ' << a[i] << ' ' << s << ' ' << lim - s << '\n';
	}
}
int main(){
	freopen("1.in", "w", stdout);
	gen(b);
	gen(c);
	int pb = 1, pc = 1;
	int s = 0, mx = 0;
	while (pb <= n || pc <= n){
		if (pc > n || (pb <= n && b[pb] <= c[pc])){
			s += b[pb];
			pb++;
		} else {
			s -= c[pc];
			pc++;
		}
		if (pb + pc >= 52) break;
		mx = max(mx, abs(s));
		cerr << s << ' ' << mx << '\n';
	}
	cout << 100 << '\n';
	for (int i = 1; i <= n; i++) cout << b[i] << ' ';
	for (int i = 1; i <= n; i++) cout << c[i] << ' ';
	cout << '\n';
	return 0;
}
