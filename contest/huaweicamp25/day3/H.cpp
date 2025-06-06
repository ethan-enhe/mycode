#include <bits/stdc++.h>
using namespace std;
map<string, int> cnt;
int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    string mx = "";
    while (n--) {
        string s;
        cin >> s;
        if (++cnt[s] > cnt[mx]) {
            mx = s;
        }
    }
    cout << mx;

    return 0;
}
