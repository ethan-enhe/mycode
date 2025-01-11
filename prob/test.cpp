#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
const int MOD = 1000000007;

vector<int> mobius;
vector<int> fact;
vector<int> inv_fact;

void compute_mobius(int n) {
    mobius.resize(n + 1, 1);
    for (int p = 2; p <= n; ++p) {
        if (mobius[p] == 1) {
            for (int multiple = p; multiple <= n; multiple += p) {
                mobius[multiple] *= -p;
            }
            for (int multiple = p * p; multiple <= n; multiple += p * p) {
                mobius[multiple] = 0;
            }
        }
        if (mobius[p] == p) {
            mobius[p] = 1;
        } else if (mobius[p] == -p) {
            mobius[p] = -1;
        } else {
            int tmp = mobius[p];
            bool square = false;
            unordered_map<int, int> factor;
            while (tmp != 1) {
                int div = mobius[tmp];
                if (factor[div]) {
                    square = true;
                    break;
                }
                factor[div] = 1;
                tmp /= div;
            }
            mobius[p] = square ? 0 : pow(-1, factor.size());
        }
    }
}
int pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * 1LL * a % mod;
        }
        a = a * 1LL * a % mod;
        b >>= 1;
    }
    return res;
}

void compute_factorials(int n, int mod) {
    fact.resize(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * 1LL * i % mod;
    }
    inv_fact.resize(n + 1, 1);
    inv_fact[n] = pow(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * 1LL * (i + 1) % mod;
    }
}

vector<int> get_divisors(int x) {
    vector<int> divs;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            divs.push_back(i);
            if (i != x / i) divs.push_back(x / i);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    compute_mobius(3000000);
    compute_factorials(3000000, MOD);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c, k;
        cin >> a >> b >> c >> k;
        vector<int> d(k);
        for (int i = 0; i < k; ++i) {
            cin >> d[i];
        }
        vector<int> div_a = get_divisors(a);
        vector<int> div_b = get_divisors(b);
        vector<int> div_c = get_divisors(c);
        long long total = 0;
        for (int da : div_a) {
            for (int db : div_b) {
                for (int dc : div_c) {
                    int m_a = a / da;
                    int m_b = b / db;
                    int m_c = c / dc;
                    int m = m_a * m_b * m_c;
                    bool valid = true;
                    for (int di : d) {
                        if (di % m != 0) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;
                    int mu = mobius[m_a] * mobius[m_b] % MOD * mobius[m_c] % MOD;
                    if (mu == 0) continue;
                    int dc_total = da * db % MOD * dc % MOD;
                    dc_total = dc_total % MOD;
                    long long term = fact[dc_total];
                    for (int di : d) {
                        int cnt = di / m;
                        term = term * 1LL * inv_fact[cnt] % MOD;
                    }
                    term = term * 1LL * mu % MOD;
                    total = (total + term) % MOD;
                }
            }
        }
        cout << total << endl;
    }
    return 0;
}
