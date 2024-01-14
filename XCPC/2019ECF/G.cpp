#include <bits/stdc++.h>
using namespace std;
const int N = 310, K = 10;
struct team {
    int prob, tim;
    vector<int> t;
};
bool operator<(const team &a, const team &b) {
    if (a.prob != b.prob) return a.prob > b.prob;
    if (a.tim != b.tim) return a.tim < b.tim;
    return a.t < b.t;
}
team tea[N];
int early = 301, late = -1;
int ear[K];

int solvet[K], pen[K];
int p[K];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < K; i++) ear[i] = 301;
    for (int i = 0; i < n - 1; i++) {
        string s;
        std::getline(cin, s);
        while (s.size() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
        if (s.empty()) {
            std::getline(cin, s);
            while (s.size() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
        }
        int left = 0;
        vector<int> t;
        int prob = 0, tim = 0;
        for (int j = 0; j < K; j++) {
            int right = left;
            while (right < s.size() && s[right] != ',') ++right;
            if (right != left + 1) {
                int mid = left;
                while (s[mid] != ' ') mid++;
                string s1, s2;
                s1 = s.substr(left, mid - left);
                s2 = s.substr(mid + 1, right - mid - 1);
                int ti = atoi(s1.c_str()), pn = atoi(s2.c_str());
                t.push_back(ti);
                prob++;
                tim += ti + pn * 20;
                early = min(early, ti);
                ear[j] = min(ear[j], ti);
                late = max(late, ti);
            }
            left = right + 1;
        }
        sort(t.begin(), t.end(), greater<int>());
        tea[i] = {prob, tim, t};
        // cerr<<"team "<<i<<" "<<prob<<" "<<tim<<endl;
    }
    sort(tea, tea + n - 1);

    string s;
    std::getline(cin, s);
    int left = 0;
    for (int j = 0; j < K; j++) {
        int right = left;
        while (right < s.size() && s[right] != ',') ++right;
        if (right != left + 1) {
            int mid = left;
            while (mid != ' ') mid++;
            string s1, s2;
            s1 = s.substr(left, mid - left);
            s2 = s.substr(mid + 1, right - mid - 1);
            int ti = atoi(s1.c_str()), pn = atoi(s2.c_str());
            solvet[j] = ti;
            pen[j] = pn;
            early = min(early, ti);
            late = max(late, ti);
        } else {
            solvet[j] = 301;
            pen[j] = 0;
        }
        left = right + 1;
    }

    int ans = 0;
    for (int i = 0; i < K; i++) p[i] = i;
    do {
        int used = 0, tim = 0, prob = 0;
        vector<int> t;
        int hap = 0;
        int first = -1, last = -1;
        for (int I = 0; I < K; I++) {
            int i = p[I];
            if (used + solvet[i] > 300) break;
            used += solvet[i];
            if (first == -1) first = used;
            last = used;
            if (used <= ear[i]) hap += 800;

            tim += used + pen[i] * 20;
            prob++;
            t.push_back(used);
        }
        sort(t.begin(), t.end(), greater<int>());
        if (first != -1 && first <= early) hap += 700;
        if (last != -1 && last >= late) hap += 500;
        team pang{prob, tim, t};

        int rk = lower_bound(tea, tea + n - 1, pang) - tea + 1;
        hap += 5000 / rk;
        if (rk <= n / 10)
            hap += 1200;
        else if (rk <= n / 10 * 3)
            hap += 800;
        else if (rk <= n / 10 * 6)
            hap += 400;

        ans = max(ans, hap);
    } while (next_permutation(p, p + K));
    cout << ans << "\n";
    return 0;
}
