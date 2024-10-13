// generate test for A.cpp
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }
int main() {
    srand(time(0));
    int n = 50000, m = randint(1, n);
    cout << n << " " << m << endl;
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin() + 1, p.end(), rng);
    for (int i = 1; i <= n; i++) {
        cout << i << " ";
    }
    return 0;
}
