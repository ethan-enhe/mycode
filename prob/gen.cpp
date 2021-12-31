#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std; 
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());


int n = 3e5, m =2e6, q = 5e6;
int a[1000005], b[1000005], g[1005][1005], idx[1000005], tmp[1000005];
int vis[1000005];


inline long long rndll() {
	return (rnd() << 31) | rnd();
}

inline void Tree0() {
	double high = 1;
	for (int i = 2;i <= n;i++) {
		double low = (n - (n - i) / 5000 - 100) / (double)n;
		int l = low * i, r = i;
		l = max(l, 1);
		r = max(r, 1);
		l = 1; r = i;
		int fa;
		printf("%d %d %d\n", fa = rnd() % (r - l) + l, i, rnd() % 2000 + 1);
		vis[fa] = 1;
	}
}

inline void Tree1() {
	double high = 1;
	for (int i = 2;i <= n;i++) {
		double low = (n - (n - i) / 500 - 10) / (double)n;
		int l = low * i, r = i;
		l = max(l, 1);
		r = max(r, 1);
		//l = 1; r = i;
		int fa;
		printf("%d %d\n", fa = rnd() % (r - l) + l, rnd() % 10 + 1);
		vis[fa]++;
	}
}

inline void Tree2() {
	for (int i = 2;i <= 150000;i++) printf("%d ", i - 1);
	for (int i = 2;i <= 150000;i++) vis[i - 1] = 1;
	int l = 150001, r;
	while (l <= 500000) {
		r = l + 1999;
		int f = rnd() % (l - 1) + 1;
		vis[f] = 1;
		for (int i = l;i <= r;i++) printf("%d ", f);
		l = r + 1;
	} 
}

inline void BinT() {
	for (int i = 2;i <= n;i++) printf("%d ", i / 2);
}

inline void Link() {
	for (int i = 2;i <= n;i++) {
		vis[i - 1] = 1;
		printf("%d %d\n", i - 1, rnd() % 2000 + 1);
	}
}

inline void Sun() {
	vis[1] = 1;
	for (int i = 2;i <= n;i++) printf("%d %d\n", 1, rnd() % 2000 + 1);
}

inline void Shuffle(int *a, int len) {
	for (int i = 1;i <= len;i++) swap(a[i], a[rnd() % i + 1]);
}

multiset <long long> st;
int k, x[10005], y[10005];
pair <int, int> l[10005], r[10005];

struct Vec {
	long double x, y;
	bool type;
	Vec() {x = y = 0;}
	Vec(long double x, long double y) : x(x), y(y) {}
	Vec operator + (const Vec& b) const {return Vec(x + b.x, y + b.y);}
	Vec operator - (const Vec& b) const {return Vec(x - b.x, y - b.y);}
	long double operator * (const Vec& b) const {return x * b.y - y * b.x;}
	bool operator < (const Vec& b) const {return y < b.y;}
	inline long double Ang() {
		return acos(x / sqrt(x * x + y * y));
	}
};
Vec p[10005];

inline bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.second < b.second;
}

const long double PI = acos(-1.0);

const int N = 5000;

inline void MaxTime() {
	cout << 5000 << " " << 5000 << " " << 500000 << " " << 500000 << " " << 1 << " " << 4 << " " << 0 << endl;
	n = 5000;
m=5000;
p[0].x= 500000;
p[n + m + 1].x = 500000;
	for (int i = 1;i <= n;i++) {
    p[i].x = 0;
    p[i].y = (i - 1) * 150;
    }
    p[n].y = 1000000;
	for (int i = 1;i <= n;i++) {
		cout << fixed << p[i].x << " " << p[i].y << endl;
    }
	for (int i = 1;i <= m;i++) {
    p[i + n].x = 1000000;
    p[i + n].y = (i - 1) * 150;
    p[i + n].type = 1;
	}
	p[n + m].y = 1000000;
	for (int i = 1;i <= m;i++) {
		cout << fixed << p[n + i].x << " " << p[n + i].y << endl;
    }
	p[n + m + 1].y = 1e6;
}

int main()
{
	srand(unsigned(time(NULL)));
	freopen("test.in","w",stdout);
	
	
	//Generator begin
	printf("%d %d %d\n", n, q, 362881);
	Tree1();
	printf("%d\n", rnd() % 10 + 1);
	for (int i = 1;i <= n;i++) {
		if (!vis[i]) printf("%d ", rnd() % 10 + 1);
	}
	puts("");
	/*
	MaxTime();return 0;
	long double ang = rnd() % 1000000 / 1000000.0 * PI;
	k = 4500 - rnd() % 200;
	n = 0; m = 0;
	for (int i = 1;i <= k - 2;i++) {
		y[i] = rnd() % 1000000;
	}
	y[k - 1] = 0; y[k] = 1000000;
	sort(y + 1, y + k + 1);
	k = unique(y + 1, y + k + 1) - y - 1;
	for (int i = 1;i <= k;i++) x[i] = rnd() % 999998 + 2;
	long double sum = 0, tmp = ang;
	for (int i = 1;i <= k;i++) {
		p[i].x = x[i]; p[i].y = y[i];
	}
	for (int i = 2;i <= k;i++) {
		sum += abs((p[i] - p[i - 1]).Ang() - tmp);
		tmp = (p[i] - p[i - 1]).Ang();
	}
	for (int i = 1;i <= k;i++) {
		if (i==1 || i==k || (p[i + 1] - p[i]).Ang() < (p[i] - p[i - 1]).Ang()) {
			l[++n] = make_pair(x[i] - rnd() % min(x[i] - (i == 1 || i == k), 20) - (i == 1 || i == k), y[i]);
			vis[y[i]] = 1;
		}
	}
	while (n <= N-1) {
		l[++n].second = rnd() % 1000000 + 1;
		if (vis[l[n].second]) {
			n--;
			continue;
		}
		for (int i = 1;i <= k;i++) {
			if (y[i] <= l[n].second && y[i + 1] > l[n].second) {
				long long lim = 1ll * (l[n].second - y[i]) * (x[i + 1] - x[i]) / (y[i + 1] - y[i]) + x[i];
				l[n].first = lim - rnd() % min(lim, 20ll);
				
				break;
			}
		}
		vis[l[n].second] = 1;
	}
	for (int i = 1;i <= k;i++) p[i].x = x[i] = 1000000 - x[i];
	for (int i = 1;i <= k;i++) {
		if (i==1 || i==k || (p[i + 1] - p[i]).Ang() < (p[i] - p[i - 1]).Ang()) {
			r[++m] = make_pair(1000000 - (x[i] - rnd() % min(x[i] - (i == 1 || i == k), 20) - (i == 1 || i == k)), y[i]);
			vis[y[i]] = 1;
		}
	}
	while (m <= N-1) {
		r[++m].second = rnd() % 1000000 + 1;
		if (vis[r[m].second]) {
			m--;
			continue;
		}
		for (int i = 1;i <= k;i++) {
			if (y[i] <= r[m].second && y[i + 1] > r[m].second) {
				long long lim = 1ll * (r[m].second - y[i]) * (x[i + 1] - x[i]) / (y[i + 1] - y[i]) + x[i];
				r[m].first = 1000001 - lim + rnd() % min(lim, 20ll);
				break;
			}
		}
		vis[r[m].second] = 1;
	}
	sort(l + 1, l + n + 1, cmp); sort(r + 1, r + m + 1, cmp);
	cout << n << " " << m << " " << 1000000 - x[1] << " " << 1000000 - x[k] << " " << 1 << " ";
	cout << fixed << setprecision(5) << max((long double)0, sum + 1e-5 - (!(rnd() % 4))) << " " << ang << endl;
	for (int i = 1;i <= n;i++) cout << l[i].first << " " << l[i].second << endl;
	for (int i = 1;i <= m;i++) cout << r[i].first << " " << r[i].second << endl;
	//for (int i = 1;i <= k;i++) cerr << 1000000 - x[i] << " " << y[i] << endl;
	*/
	//Generator end
	
	return 0;
}
