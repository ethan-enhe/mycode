#include <bits/stdc++.h>

#include <algorithm>
#include <queue>
#include <random>
#include <vector>
using namespace std;
const int MXD = 1025;
const int MXN = 5e4 + 50;
const int NR = MXN << 1;
using f = float;
const f INF = 1e9;
int n, d;
// template <typename T = f, const int L = MXD>
struct vec {
    array<f, MXD> v;
    void clear() {
        for (int i = 1; i < d; i++) v[i] = 0;
    }
    vec operator-(const vec &b) const {
        vec res;
        for (int i = 0; i < d; i++) res.v[i] = v[i] - b.v[i];
        return res;
    }
    vec operator+(const vec &b) const {
        vec res;
        for (int i = 0; i < d; i++) res.v[i] = v[i] + b.v[i];
        return res;
    }
    vec operator*(const vec &b) const {
        vec res;
        for (int i = 0; i < d; i++) res.v[i] = v[i] * b.v[i];
        return res;
    }
    f sum() const {
        f res = 0;
        for (int i = 0; i < d; i++) res += v[i] * v[i];
        return res;
    }
    f dis(const vec &b, f ub = INF) const {
        f res = 0, tmp;
        for (int i = 0; i < d; i++) {
            tmp = v[i] - b.v[i];
            res += tmp * tmp;
            if (res > ub) return ub;
        }
        return res;
    }
};

struct node {
    int id;
    int splitd;
    f splitmid;
    int ls, rs;
} t[NR];

int nodec, rt;
vec arr[MXN];
int id[MXN];

int cmpd;
bool cmp(int x, int y) { return arr[x].v[cmpd] < arr[y].v[cmpd]; }
void build(int &p, int l, int r) {
    if (l > r) return;
    if (!p) p = ++nodec;

    vec s, s2;
    s.clear();
    s2.clear();
    for (int j = l; j <= r; j++) {
        int i = id[j];
        s = s + arr[i];
        s2 = s2 + arr[i] * arr[i];
    }
    int argmx = 0;
    for (int i = 0; i < d; i++) {
        s.v[i] /= (r - l + 1);
        s2.v[i] = s2.v[i] / (r - l + 1) - s.v[i] * s.v[i]; // var
        if (s2.v[i] > s2.v[argmx]) argmx = i;
    }
    int mid = (l + r) >> 1;
    t[p].splitd = argmx;
    cmpd = argmx;
    nth_element(id + l + 1, id + l + mid, id + r + 1, cmp);
    t[p].splitmid = arr[id[mid]].v[argmx];
    t[p].id = id[mid];
    build(t[p].ls, l, mid - 1);
    build(t[p].rs, mid + 1, r);
}
priority_queue<pair<f, int>> q;

int k;
vec qx;
vec low, upp;
f pred_near() {
    f res = 0, tmp;
    for (int i = 0; i < d; i++) {
        if (low.v[i] > qx.v[i])
            tmp = low.v[i] - qx.v[i];
        else if (upp.v[i] < qx.v[i])
            tmp = upp.v[i] - qx.v[i];
        else
            tmp = 0;
        res += tmp * tmp;
    }
    return res;
}
bool tryins(f dis, int id = 0, bool put = 0) {
    // cerr << dis << " " << id << " " << put << '\n';
    if (q.size() < k) {
        if (put) q.push({dis, id});
        return 1;
    }
    if (dis < q.top().first) {
        if (put) {
            q.pop();
            q.push({dis, id});
        }
        return 1;
    }
    return 0;
}
void qry(int p) {
    if (!p) return;
    if (!tryins(pred_near())) return;
    f cur = arr[t[p].id].dis(qx);
    tryins(cur, t[p].id, 1);
    // cerr << p << " " << t[p].id << " " << cur << " " << q.size()<<" " << (q.empty() ? 0 : q.top().first) << '\n';
    int spd = t[p].splitd;
    int savelx = low.v[spd];
    int saveux = upp.v[spd];
    upp.v[spd] = t[p].splitmid;
    qry(t[p].ls);
    upp.v[spd] = saveux;
    low.v[spd] = t[p].splitmid;
    qry(t[p].rs);
    low.v[spd] = savelx;
}
vector<int> force() {
    vector<pair<f, int>> id;
    vector<int> r;
    for (int i = 1; i <= n; i++) {
        id.push_back({arr[i].dis(qx), i});
    }
    sort(id.begin(), id.end());
    // cerr << "!!!" << k << '\n';
    for (int i = k - 1; i >= 0; i--) {
        r.push_back(id[i].second);
        // cerr << id[i].first << '\n';
    }
    return r;
}
mt19937 mr(clock());
f rd() {
    uniform_real_distribution<f> rnd(-10000, 10000);
    return rnd(mr);
}

int main() {
    // cerr << (sizeof(v) >> 20);
    ios::sync_with_stdio(0);
    cin.tie(0);
    n = 50000, d = 1000;
    cout << n << " " << d << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < d; j++) {
            arr[i].v[j] = rd();
            cout << arr[i].v[j] << " ";
        }
        cout << '\n';
    }
    cout << 10 << '\n';
    int q = 800;
    while (q--) {
        for (int j = 0; j < d; j++) {
            cout << rd() << " ";
        }
        cout << '\n';
    }
    cout << "end";

    return 0;
}
