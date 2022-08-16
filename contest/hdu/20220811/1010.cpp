
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#define double long double
using namespace std;
inline int getint() {
    int ans = 0, f = 1;
    char c = getchar();
    while (c > '9' || c < '0') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * f;
}
const double eps = 1e-13, pi = 3.141592653589793238462643383;
inline bool equ(double x, double y) { return std::abs(x - y) < eps; }
struct point {
    double x, y;
    point() {}
    point(double X, double Y) { x = X, y = Y; }
#if __cplusplus > 201103
    point(initializer_list<double> p) {
        if (p.size() < 2) return;
        auto P = p.begin();
        x = *P;
        ++P;
        y = *P;
    }
#endif
};
ostream &operator<<(ostream &os, const point p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
typedef point vec;
double cross(vec a, vec b) { // 向量叉积
    return (a.x * b.y - b.x * a.y);
}
double dot(vec a, vec b) { // 向量点积
    return (a.x * b.x + a.y * b.y);
}
vec operator-(vec a) { // 相反向量
    return vec(-a.x, -a.y);
}
vec operator-(point a, point b) { // 两点之间的向量 / 向量求差 / 点减向量
    return vec(a.x - b.x, a.y - b.y);
}
vec operator+(vec a, vec b) { // 向量求和 / 点加向量
    return vec(a.x + b.x, a.y + b.y);
}
vec operator*(vec a, double b) { // 向量数积
    return vec(a.x * b, a.y * b);
}
vec operator/(vec a, double b) { // 向量数除
    return vec(a.x / b, a.y / b);
}
bool operator==(point a, point b) { // 相等
    return equ(a.x, b.x) && equ(a.y, b.y);
}
bool operator!=(point a, point b) { // 不等
    return !(equ(a.x, b.x) && equ(a.y, b.y));
}
double dis(point a, point b = point(0, 0)) { // 两点距离
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double dis2(point a, point b = point(0, 0)) { // 两点距离
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double atan2(vec p) { // 向量极角
    return atan2(p.y, p.x);
}
vec rotate(point p, double theta, point center = point(0, 0)) { // 点 p 绕 center 逆时针旋转 theta 弧度
    p = p - center;
    theta = -theta;
    return point(p.x * cos(theta) + p.y * sin(theta), p.y * cos(theta) - p.x * sin(theta)) + center;
}
vec rotate90(vec p) { // 向量 p 逆时针旋转 90 度
    return point(-p.y, p.x);
}
bool cmp(point x, point y) { // 比较极角大小
    if (x.y * y.y < -eps) return x.y > y.y;
    if (equ(x.y, 0) && equ(y.y, 0) && x.x * y.x < 0) return x.x > y.x;
    if (equ(cross(y, x), 0)) return std::abs(x.x) < std::abs(y.x);
    return cross(x, y) > 0;
}

struct line {
    point a, b;
    line() {}
    line(point A, point B) { a = A, b = B; }
#if __cplusplus > 201103
    line(initializer_list<point> p) {
        if (p.size() < 2) return;
        auto P = p.begin();
        a = *P;
        ++P;
        b = *P;
    }
#endif
};
ostream &operator<<(ostream &os, const line l) {
    os << "[" << l.a << " -- " << l.b << "]";
    return os;
}
line operator-(line l) { // 直线反向
    return line(l.b, l.a);
}
point inter(line a, line b) { // 直线求交
    double s1 = cross(b.a - a.a, b.b - a.a), s2 = cross(b.b - a.b, b.a - a.b);
    if (equ(s1 + s2, 0)) {
        return point(-1e12, -1e12);
    }
    return point(a.a.x + (a.b.x - a.a.x) / (s1 + s2) * s1, a.a.y + (a.b.y - a.a.y) / (s1 + s2) * s1);
}
bool isleft(line l, point p) { // 点在直线左侧
    return cross(l.b - l.a, p - l.a) > -eps;
}
bool isin(line a, line b) { // 直线 a 在 b 的左侧
    return isleft(b, a.a);
}
struct ray : line {
    ray() {}
    ray(point A, point B) { a = A, b = B; }
#if __cplusplus > 201103
    ray(initializer_list<point> p) {
        if (p.size() < 2) return;
        auto P = p.begin();
        a = *P;
        ++P;
        b = *P;
    }
#endif
};
struct segment : ray {
    segment() {}
    segment(point A, point B) { a = A, b = B; }
    point mid() { return (a + b) / 2; }
    line pb() { // 垂直平分线（perpendicular_bisector）
        return line(mid(), mid() + rotate90(a - b));
    }
    vec to_vec() const { return b - a; }
#if __cplusplus > 201103
    segment(initializer_list<point> p) {
        if (p.size() < 2) return;
        auto P = p.begin();
        a = *P;
        ++P;
        b = *P;
    }
#endif
};
bool ison(point p, line l) { // 点在直线上
    return equ(cross(p - l.a, l.b - l.a), 0);
}
bool ison(point p, ray r) { // 点在射线上
    return ison(p, line(r)) && dot(p - r.a, r.b - r.a) > eps;
}
bool ison(point p, segment s) { // 点在线段上
    return ison(p, ray(s)) && ison(p, ray(s.b, s.a));
}
bool iscross(line l, segment b) { // 线段与直线是否相交
    if (ison(b.a, l) || ison(b.b, l)) return 1;
    if (equ(cross(l.b - l.a, b.b - b.a), 0)) return 0;
    point p = inter(l, line(b));
    return ison(p, b);
}
bool iscross(segment b, line l) { // 线段与直线是否相交
    return iscross(l, b);
}
bool iscross(segment a, segment b) { // 线段与线段是否相交
    if (max(a.a.x, a.b.x) < min(b.a.x, b.b.x) - eps) return 0;
    if (max(a.a.y, a.b.y) < min(b.a.y, b.b.y) - eps) return 0;
    if (max(b.a.x, b.b.x) < min(a.a.x, a.b.x) - eps) return 0;
    if (max(b.a.x, b.b.x) < min(a.a.x, a.b.x) - eps) return 0;
    return iscross(line(a), b) && iscross(line(b), a);
}
point footpoint(line l, point p) { // 点到直线的垂足
    if (ison(p, l)) return p;
    return l.a + (l.b - l.a) * dot(p - l.a, l.b - l.a) / dis2(l.a, l.b);
}
point footpoint(segment l, point p) { // 点到线段的最近点
    if (dot(l.b - l.a, p - l.a) < 0) return l.a;
    if (dot(l.a - l.b, p - l.b) < 0) return l.b;
    return footpoint(line(l), p);
}
double dis(line l, point p) { // 点到直线的距离
    return std::abs(cross(l.b - l.a, p - l.a) * 2 / dis(l.b, l.a));
}
double dis(ray l, point p) { // 点到射线的距离
    if (dot(l.b - l.a, p - l.a) < 0)
        return dis(p, l.a);
    else
        return dis(line(l), p);
}
double dis(segment l, point p) { // 点到线段的距离
    if (dot(l.b - l.a, p - l.a) < 0) return dis(p, l.a);
    if (dot(l.a - l.b, p - l.b) < 0)
        return dis(p, l.b);
    else
        return dis(line(l), p);
}
point symmetry(point o, point p) { // 点关于点对称
    return point(o.x * 2 - p.x, o.y * 2 - p.y);
}
point symmetry(line l, point p) { // 点关于直线对称
    point q = footpoint(l, p);
    return symmetry(q, p);
}

struct circle {
    point o;
    double r;
    circle() {}
    circle(point O, double R) {
        o = O;
        r = R;
    }
    circle(double x, double y, double R) {
        o = point(x, y);
        r = R;
    }
};
bool isin(point p, circle c) { // 点在圆内
    return dis(p, c.o) - c.r < eps;
}
bool ison(point p, circle c) { // 点在圆上
    return equ(dis(p, c.o), c.r);
}
point symmetry(circle c, point p) { // 点关于圆对称
    return p * c.r * c.r / dis2(p);
}

struct triangle {
    point a, b, c;
    triangle() {}
    triangle(point A, point B, point C) {
        a = A;
        b = B;
        c = C;
    }
#if __cplusplus > 201103
    triangle(initializer_list<point> p) {
        if (p.size() < 3) return;
        auto P = p.begin();
        a = *P;
        ++P;
        b = *P;
        ++P;
        c = *P;
    }
#endif
    bool iscollinear() { // 三点共线
        return equ(cross(b - a, c - a), 0);
    }
    point circumcenter() { // 外心
        if (!iscollinear()) return inter(segment(a, b).pb(), segment(a, c).pb());
        if (ison(b, segment(a, c))) return segment(a, c).mid();
        if (ison(a, segment(b, c))) return segment(b, c).mid();
        return segment(a, b).mid();
    }
    circle circumcircle() { // 外接圆
        point o = circumcenter();
        return circle(o, dis(o, a));
    }
};

struct polygon {
    vector<point> p;
    polygon() {}
    polygon(vector<point> p) : p(p) {}
#if __cplusplus > 201103
    polygon(initializer_list<point> p) : p(p) {}
#endif
    int _(int x) const { return x >= p.size() ? x - p.size() : x; }
    int size() const { return p.size(); }
    point operator[](int x) const { // 第 x 个点
        if (x < 0)
            x += size();
        else if (x >= size())
            x -= size();
        if (x >= 0 && x < size())
            return p[x];
        else
            return p[_(x % size() + size())];
    }
    segment side(int x) const { // 第 x 条边
        if (x < 0)
            x += size();
        else if (x >= size())
            x -= size();
        if (x >= 0 && x < size())
            return segment(p[x], p[_(x + 1)]);
        else {
            x = _(x % size() + size());
            return segment(p[x], p[_(x + 1)]);
        }
    }
    bool iscounterclockwise();
    double S() const { // 面积
        double s = cross(p[size() - 1], p[0]);
        for (int i = 0; i < p.size() - 1; i++) s += cross(p[i], p[i + 1]);
        return s / 2;
    }
    double C() const { // 周长
        double s = dis(p[size() - 1], p[0]);
        for (int i = 0; i < p.size() - 1; i++) s += dis(p[i], p[i + 1]);
        return s / 2;
    }
};
bool ison(point p, const polygon &a) { // 点是否在多边形上
    for (int i = 0; i < a.size(); i++)
        if (ison(p, a.side(i))) return 1;
    return 0;
}
bool isin_(point p, const polygon &a) { // 点是否在多边形内（边界条件可能出锅）
    double theta = rand();
    segment r(p, p + rotate(vec(0, 1e12), theta));
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) cnt += iscross(a.side(i), r);
    return cnt & 1;
}
bool isin(point p, const polygon &a) { // 点是否在多边形内
    return isin_(p, a) || ison(p, a);
}
bool isin_strict(point p, const polygon &a) { // 点是否严格在多边形内
    return isin_(p, a) && !ison(p, a);
}

inline int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    return x < 0 ? -1 : 1;
}
struct convex : polygon {
    void construct(vector<point> q) { // 构造凸包
        p.clear();
        int n = q.size();
        for (int i = 1; i < n; i++)
            if (q[i].y < q[0].y || (equ(q[i].y, q[0].y) && q[i].x < q[0].x)) swap(q[i], q[0]);
        point q0 = q[0];
        for (int i = n - 1; i >= 0; --i) q[i].x -= q[0].x, q[i].y -= q[0].y;
        sort(q.begin() + 1, q.end(), cmp);
        p.push_back(q[0]);
        p.push_back(q[1]);
        for (int i = 2; i < n;) {
            if (p.size() >= 2 && cross(q[i] - p[p.size() - 2], p.back() - p[p.size() - 2]) >= 0)
                p.pop_back();
            else
                p.push_back(q[i++]);
        }
        for (int i = 0; i < p.size(); i++) p[i] = p[i] + q0;
    }
    void Andrew(vector<point> node) {
        int n = node.size();
        p.resize(n * 2);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            while (cnt > 1 && sgn(cross(p[cnt - 1] - p[cnt - 2], node[i] - p[cnt - 2])) <= 0) cnt--;
            p[cnt++] = node[i];
        }
        int j = cnt;
        for (int i = n - 2; i >= 0; i--) {
            while (cnt > j && sgn(cross(p[cnt - 1] - p[cnt - 2], node[i] - p[cnt - 2])) <= 0) cnt--;
            p[cnt++] = node[i];
        }
        if (n > 1) cnt--;
        p.resize(cnt);
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<point> p;
        sort(p.begin(), p.end(), [&](const point &x, const point &y) { return x.x == y.x ? x.y < y.y : x.x < y.x; });
        p.resize(unique(p.begin(), p.end()) - p.begin());
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            p.push_back(point(x, y));
        }
        double l = 0;
        double s = 0;
        // cerr<<"~ "<<c.p.size()<<endl;
        if (p.size() == 1) {
            l = 0;
        } else {
            convex c;
            c.Andrew(p);
            // point p0,p1,p2,p3;
            for (int i = 0; i < c.p.size(); i++) {
                // cerr<<"? "<<c[i]<<endl;
                // if(cross({-1.,-1.},c[i]-c[i-1])<=0&&cross({-1.,-1.},c[i+1]-c[i])>0)p0=c[i];
                // if(cross({ 1.,-1.},c[i]-c[i-1])<=0&&cross({ 1.,-1.},c[i+1]-c[i])>0)p1=c[i];
                // if(cross({ 1., 1.},c[i]-c[i-1])<=0&&cross({ 1., 1.},c[i+1]-c[i])>0)p2=c[i];
                // if(cross({-1., 1.},c[i]-c[i-1])<=0&&cross({-1., 1.},c[i+1]-c[i])>0)p3=c[i];
                l += max(abs(c[i].x - c[i - 1].x), abs(c[i].y - c[i - 1].y));
            }
            // l=abs(p0.y-p1.y)+abs(p1.x-p2.x)+abs(p2.y-p3.y)+abs(p3.x-p0.x);
            // cerr<<"> "<<p0<<" "<<p1<<" "<<p2<<" "<<p3<<endl;
            s = c.S();
        }

        while (q--) {
            int t;
            cin >> t;
            double ans = s * 2 + (t * 2.) * (t * 2) + 2. * l * t;
            long long ans2 = round(ans);
            cout << ans2 / 2 << "."
                 << "05"[ans2 % 2] << "\n";
        }
    }
}
