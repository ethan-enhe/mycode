# include <bits/stdc++.h>
# define ll long long
using namespace std;
const int MAXN = 1000000;
int n;
char s[MAXN];
int a[MAXN];
int lst[MAXN][3];
int p;
char obuf[1 << 20];
void pc(char x){
	obuf[p++] = x;
	if (p == (1 << 20)) fwrite(obuf, (1 << 20), 1, stdout);
	p &= ((1 << 20) - 1);
}
void write(int x){
	if (x >= 10) write(x / 10);
	pc(x % 10 + '0');
}
void add(int u, int v){
	write(u);
	pc(' ');
	write(v);
	pc('\n');
}
void work(int l, int r){
	if (r - l + 1 <= 3) return;
	int nc = 3 - a[r] - a[l];
	if (a[l + 1] == nc && a[r - 1] == nc){
		if (a[l + 2] == a[l]){
			add(l + 1, r);
			work(l + 1, r);
		} else {
			add(l, r - 1);
			work(l, r - 1);
		}
	} else if (a[l + 1] == nc){
		add(l + 1, r);
		work(l + 1, r);
	} else if (a[r - 1] == nc){
		add(l, r - 1);
		work(l, r - 1);
	} else {
		int pos = lst[r][nc];
		add(l, pos);
		add(r, pos);
		work(l, pos);
		work(pos, r);
	}
}
int main(){
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d", &n);
	scanf("%s", s + 1);
	s[n + 1] = s[1];
	for (int i = 1; i <= n; i++){
		if (s[i] == s[i + 1]){
			printf("Impossible!\n");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++){
		if (s[i] == 'R') a[i] = 0;
		else if (s[i] == 'G') a[i] = 1;
		else a[i] = 2;
		memcpy(lst[i], lst[i - 1], sizeof(lst[i]));
		lst[i][a[i]] = i;
	}
	if (!lst[n][0] || !lst[n][1] || !lst[n][2]){
		printf("Impossible!\n");
		return 0;
	}
	work(1, n);
	fwrite(obuf, p, 1, stdout);
	return 0;
}

