// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
//{{{ Def
#define fi first
#define se second
#define vec vector
#define all(x) (x).begin(), (x).end()
#define unq(x) (x).erase(unique(all(x)), (x).end())
#define tpl template <typename T>

typedef long long ll;
//}}}
//{{{ Func
ll ri(const ll &l, const ll &r) { return rand() % (r - l + 1) + l; }
//}}}
const ll P = 1e9 + 7;
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;
string s;

struct prob {
    string ask;
    char ans;
    int cnt;
};

prob parse(string str) {
    prob ans;
    int ansind = -1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') ansind = i;
        if ((str[i] == '\n' || str[i] == '\r') && ansind != -1) break;
    }
    ans.ans = str[ansind];
    ans.ask = str.substr(0, ansind) + str.substr(ansind + 1);
    ans.cnt = 1;
    return ans;
}
vector<prob> all;

void read_prob() {
    string tmp, str;
    while (getline(cin, tmp)) {
        if (tmp[0] == 'q') break;
        if (!tmp.empty() && isdigit(tmp[0])) {
            if (!str.empty()) all.push_back(parse(str));
            str = "";
        }
        str += tmp + "\n";
    }
    if (!str.empty()) all.push_back(parse(str));
}

int main() {
    srand(time(NULL));
    read_prob();

    while (all.size()) {
        system("cls");
        int ind = ri(0, all.size() - 1);
        cout << "Remaining problems: " << all.size() << endl;
        cout << all[ind].ask;
        --all[ind].cnt;
        char ans = getchar();
        if (ans == all[ind].ans) {
            cout << "Correct" << endl;
            if (all[ind].cnt == 0) all.erase(all.begin() + ind);
        } else {
            cout << "Incorrect: " << endl;
            cout << all[ind].ans << endl;
            all[ind].cnt = 2;
        }
        getchar();
        getchar();
    }
    cout << "Complete";
    getchar();

    return 0;
}
