// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(...) 42
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pi = pair<ll, ll>;
//}}}
//{{{ Func
tpl pair<T, T> &operator+=(pair<T, T> &x, const pair<T, T> &y) { return x.fi += y.fi, x.se += y.se, x; }
tpl pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi + y.fi, x.se + y.se}; }
tpl pair<T, T> &operator-=(pair<T, T> &x, const pair<T, T> &y) { return x.fi -= y.fi, x.se -= y.se, x; }
tpl pair<T, T> operator-(const pair<T, T> &x, const pair<T, T> &y) { return {x.fi - y.fi, x.se - y.se}; }
tpl pair<T, T> &operator*=(pair<T, T> &x, const ll &y) { return x.fi *= y, x.se *= y, x; }
tpl pair<T, T> operator*(const pair<T, T> &x, const ll &y) { return {x.fi * y, x.se * y}; }
tpl istream &operator>>(istream &is, pair<T, T> &y) { return is >> y.fi >> y.se; }
tpl ostream &operator<<(ostream &os, const pair<T, T> &y) { return os << '(' << y.fi << ',' << y.se << ')'; }
tpl T qpow(T x, ll y) {
    T r(1);
    while (y) {
        if (y & 1) r = r * x;
        x = x * x, y >>= 1;
    }
    return r;
}
ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (!a || !b) return a | b;
    ll U = __builtin_ctzll(a), V = __builtin_ctzll(b);
    a >>= U, b >>= V;
    if (U > V) U = V;
    while (a) {
        if (a < b) swap(a, b);
        a -= b;
        a >>= __builtin_ctzll(a);
    }
    return b << U;
}
tpl void umx(T &x, const T &y) { x = max(x, y); }
tpl void umn(T &x, const T &y) { x = min(x, y); }
bool inrng(const ll &x, const ll &l, const ll &r) { return l <= x && x <= r; }
bool insqr(const pi &x, const pi &lt, const pi &rb) {
    return lt.fi <= x.fi && x.fi <= rb.fi && lt.se <= x.se && x.se <= rb.se;
}
void setp(const ll &x) {
    cout.flags(ios::fixed);
    cout.precision(x);
}
template <typename T = ll>
T nxt() {
    T x;
    cin >> x;
    return x;
}
mt19937_64 mr(chrono::system_clock::now().time_since_epoch().count());
ll ri(const ll &l, const ll &r) { return uniform_int_distribution<ll>(l, r)(mr); }
ld rd(const ld &l, const ld &r) { return uniform_real_distribution<ld>(l, r)(mr); }
//}}}
const ll P = 1e9 + 7;
//{{{ Type
inline int redu(const int &x) { return x >= P ? x - P : x; }
inline int incr(const int &x) { return x + ((x >> 31) & P); }
struct mod {
    int v;
    mod() {}
    tpl mod(const T &_v) : v(_v) { assert(_v >= 0 && _v < P); }
    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mod &operator+=(const mod &y) { return v = redu(v + y.v), *this; }
    mod &operator-=(const mod &y) { return v = incr(v - y.v), *this; }
    mod &operator*=(const mod &y) { return v = (ll)v * y.v % P, *this; }
    mod &operator/=(const mod &y) { return v = (ll)v * qpow(y, P - 2).v % P, *this; }
    mod operator+(const mod &y) const { return mod(*this) += y; }
    mod operator-(const mod &y) const { return mod(*this) -= y; }
    mod operator*(const mod &y) const { return mod(*this) *= y; }
    mod operator/(const mod &y) const { return mod(*this) /= y; }
    bool operator==(const mod &y) const { return v == y.v; }
    bool operator!=(const mod &y) const { return v != y.v; }
    friend istream &operator>>(istream &is, mod &y) {
        ll x;
        is >> x;
        return y.v = incr(x % P), is;
    }
    friend ostream &operator<<(ostream &os, const mod &y) { return os << y.v; }
};
//}}}
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

vector<string> ans = {"D", "D", "B", "A", "B", "B", "B", "A", "B", "B",
                      "D", "A", "B", "B", "A", "D", "D", "B", "A", "A"};
vector<string> ask = {
    "1.	中国科学技术大学的校训是（  ）。",
    "A.勤奋学习、红专并进     B.创寰宇学府、育天下英才",
    "C.又红又专、理实交融     D.红专并进、理实交融",
    "2.	党的最高理想和最终目标是实现（  ）。",
    "A.“中国梦”              B.中华民族伟大复兴",
    "C.发展先进生产力          D.共产主义",
    "3.	伟大的革命先行者（  ）领导的辛亥革命是一次伟大的资产阶级民主革命。",
    "A.康有为     B.孙中山    C.陈独秀     D.李大钊",
    "4.	中国共产主义青年团是中国共产党领导的（   ）的群众组织。",
    "A.先进青年   B.知识分子   C.工人阶级   D.青年学生",
    "5.	（  ），中国共产党第一次全国代表大会在上海召开，最后一天会议转移至浙江嘉兴南湖举行。",
    "A.1921年7月1日         B.1921年7月23日",
    "C.1921年7月21日        D.1921年7月11日",
    "6.	《共产党宣言》第一个中文全译本的译者是（  ）。",
    "A.李大钊     B. 陈望道    C. 陈独秀     D.毛泽东",
    "7.	以下哪一项不是中共一大制定的纲领？（  ）",
    "A.以无产阶级革命军队推翻资产阶级",
    "B.推翻国际帝国主义的压迫，达到中华民族完全独立",
    "C.废除资本私有制",
    "D.采用无产阶级专政，以达到阶级斗争的目的——消灭阶级",
    "8.	中国共产党创建的第一个农村革命根据地是（  ）。",
    "A.井冈山革命根据地        B.闽北革命根据地",
    "C.鄂豫皖革命根据地        D.湘鄂西革命根据地",
    "9.	确立党对军队的绝对领导开始于（  ）。",
    "A.秋收起义   B.三湾改编   C.古田会议   D.八七会议",
    "10.	一二•九运动首先发生在（  ）。",
    "A.上海       B.北平       C.南京       D.南昌",
    "11.	我国根本国家制度即国体是（  ）。",
    "A.人民代表大会制度        B.民族区域自治制度",
    "C.多党合作与政治协商制度  D.人民民主专政",
    "12.	社会主义初级阶段基本路线的中心是（  ）。",
    "A.经济建设                B.改革开放",
    "C.保持社会稳定            D.坚持走社会主义道路",
    "13.	中国共产党的最大优势是（  ）。",
    "A.实事求是                B.密切联系群众",
    "C.建立了人民民主专政      D.全心全意为人民服务",
    "14.	习近平近日在宁夏考察时强调，要巩固提升脱贫成果，保持现有政策总体稳定，推进全面脱贫与（  ）有效衔接。",
    "A.城乡融合发展            B. 乡村振兴战略",
    "C.农业产业化发展          D. 美丽乡村建设",
    "15.	"
    "党中央团结带领全党全国各族人民，把脱贫攻坚摆在治国理政突出位置，充分发挥党的领导和我国社会主义制度的政治优势，采取"
    "了许多具有原创性、独特性的重大举措，组织实施了人类历史上（  ）的脱贫攻坚战。",
    "A.规模最大、 力度最强     B.规模最大、 速度最快",
    "C.速度最快、 难度最大     D.力度最强、 难度最大",
    "16.	"
    "修订后的《中国共产党党员权利保障条例》要求，广大党员要正确认识和处理义务和权利的辩证统一关系，行使权利必须以（  "
    "）为前提。",
    "A.履行义务   B.担当责任   C.遵守纪律    D.以上都是",
    "17.	（  ）负责团支部全面工作。",
    "A.团支部成员              B.团支部委员会",
    "C.上级团组织              D.团支部书记",
    "18.	 “五四精神”的核心内容是（  ）。",
    "A.爱国、互助、团结、奋进  B.爱国、进步、民主、科学",
    "C.进步、团结、民主、科学  D.进步、奉献、友爱、奋进",
    "19.	中国共产主义青年团团徽的内容为团旗、齿轮、（  ）、初升的太阳及其光芒，写有“中国共青团”五字的绶带。",
    "A.麦穗       B.穗稻       C. 麦稻        D.麦子",
    "20.	全国科技工作者日是（  ）。",
    "A.5月30日  B.6月30日  C.5月29日  D.6月29日"};
int main() {
    system("chcp 65001");
    system("cls");
    ask.push_back("1");
    int ind = 0, cnt = 0;
    int c = 0;
    while (cnt < ans.size()) {
        system("cls");
        do {
            cout << ask[ind++] << endl;
        } while (!isdigit(ask[ind][0]));
        cout << "请输入答案（一个大写字母），并回车:";
        string x;
        cin >> x;
        c += x == ans[cnt];
        ++cnt;
    }
    system("cls");
    cout << "正确率：" << c << "/" << ans.size() << "=" << ((double)c / ans.size() * 100) << "%" << endl;
    cout << "校验码：" << (ll)(ri(1, 0) == 1 ? 114514 : 1919810) * ri(1, 1000000000);
    ll x;
    cin >> x;

    return 0;
}
