#include <bits/stdc++.h>
using namespace std;
int n;
int x, y;
map<pair<int, int>, char> a;
char walk(char c) {
    cout << c << endl;
    char res = 'x';
    cin >> res;
    if (res == 'G') exit(0);
    if (c == '^') x--;
    if (c == 'v') x++;
    if (c == '<') y--;
    if (c == '>') y++;
    a[{x, y}] = res;
    return res;
}
void to(int tx, int ty) {
    while (x < tx) walk('v');
    while (x > tx) walk('^');
    while (y < ty) walk('>');
    while (y > ty) walk('<');
}
bool is_inside(int u, int d, int l, int r) {
    int in = 0, out = 0;
    for (int i = l; i <= r; i++) {
        //cerr<<"~ "<<d<<" "<<i<<" "<<a[{d, i}]<<"  "<<a[{d+1, i}] <<endl;
        if (a[{u - 1, i}] == 'v') in++;
        if (a[{u, i}] == '^') out++;
        if (a[{d, i}] == 'v') out++;
        if (a[{d + 1, i}] == '^') in++;
    }
    for (int i = u; i <= d; i++) {
        if (a[{i, l - 1}] == '>') in++;
        if (a[{i, l}] == '<') out++;
        if (a[{i, r}] == '>') out++;
        if (a[{i, r + 1}] == '<') in++;
    }
    if (u <= n + 1 && n + 1 <= d && l <= n + 1 && n + 1 <= r) {
        in++;
    }
    //cerr<<"> "<<u<<" "<<d<<" "<<l<<" "<<r<<"  "<<in<<" "<<out<<endl;
    return in > out;
}
void solve(int u, int d, int l, int r, bool ho) {
    //cerr<<"> "<<u<<" "<<d<<" "<<l<<" "<<r<<" "<<ho<<endl;
    if((d - u + 1) * 1ll * (r - l + 1) <= 50) {
        to(u, l);
        for (int i = 1; i <= d - u + 1; i++) {
            for (int j = 1; j < r - l + 1; j++) {
                walk(i & 1 ? '>' : '<');
            }
            walk('v');
        }
        return;
    }
    int u1 = u, d1 = d, l1 = l, r1 = r;
    int u2 = u, d2 = d, l2 = l, r2 = r;
    if (ho) {
        int midx = (d + u) / 2;
        string s;
        if (u == 1 && d == n * 2 + 1) {
            s = string(n, '>') + string(1, 'v') + string(n * 2, '<') + string(1, '^') + string(n, '>');
        } else if (abs(y - l) < abs(y - r)) {
            to(midx, l);
            s = string(r-l, '>') + string(1, 'v') + string(r-l, '<') + string(1, '^');
        } else {
            to(midx, r);
            s = string(r-l, '<') + string(1, 'v') + string(r-l, '>') + string(1, '^');
        }
        for (auto c : s) walk(c);
        d1 = midx;
        u2 = midx + 1;
    } else {
        int midy = (l + r) / 2;
        string s;
        if (abs(x - u) < abs(x - r)) {
            to(u, midy);
            s = string(d-u, 'v') + string(1, '>') + string(d-u, '^') + string(1, '<');
        } else {
            to(d, midy);
            s = string(d-u, '^') + string(1, '>') + string(d-u, 'v') + string(1, '<');
        }
        for (auto c : s) walk(c);
        r1 = midy;
        l2 = midy + 1;
    }
    if (is_inside(u1, d1, l1, r1)) {
        solve(u1, d1, l1, r1, !ho);
    } else {
        solve(u2, d2, l2, r2, !ho);
    }
}

int main() {
    cin >> n;
    x = n + 1, y = n + 1;
    solve(1, n * 2 + 1, 1, n * 2 + 1, 1);
}
