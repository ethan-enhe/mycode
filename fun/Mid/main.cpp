#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;

struct VectorSet {
    int n, d;
    vector<bitset<MAXN>> basis;
    vector<bitset<MAXN>> comb;
    vector<int> pivot_pos;

    void gaussian_elimination(vector<bitset<MAXN>>& vectors) {
        basis.resize(d);
        comb.resize(d);
        pivot_pos.assign(d, -1);

        for (int i = 0; i < d; ++i) comb[i].set(i);

        for (int col = n - 1, row = 0; col >= 0 && row < d; --col) { // 从最高位列开始消元
            int pivot = -1;
            for (int i = row; i < d; ++i) {
                if (vectors[i][col]) {
                    pivot = i;
                    break;
                }
            }
            if (pivot == -1) continue;

            swap(vectors[row], vectors[pivot]);
            swap(comb[row], comb[pivot]);

            for (int i = 0; i < d; ++i) {
                if (i != row && vectors[i][col]) {
                    vectors[i] ^= vectors[row];
                    comb[i] ^= comb[row];
                }
            }
            basis[row] = vectors[row];
            pivot_pos[row] = col;
            ++row;
        }
    }

    vector<int> solve() {
        for (int i = 0; i < d; ++i) {
            int cnt = basis[i].count();
            if (d <= cnt && cnt <= n - d + 1) {
                return bitset_to_indices(comb[i]);
            }
        }

        bitset<MAXN> sum_vec, sum_comb;
        for (int i = 0; i < d; ++i) {
            sum_vec ^= basis[i];
            sum_comb ^= comb[i];
            int cnt = sum_vec.count();
            if (d <= cnt && cnt <= n - d + 1) {
                return bitset_to_indices(sum_comb);
            }
        }
        return {};
    }

    vector<int> bitset_to_indices(const bitset<MAXN>& bs) {
        vector<int> res;
        for (int i = 0; i < d; ++i)
            if (bs[i]) res.push_back(i);
        return res;
    }
};

int main() {
    int d;
    cin >> d;
    int n = 3 * d - 3;

    vector<bitset<MAXN>> vectors(d);
    for (int i = 0; i < d; ++i) {
        string s;
        cin >> s;
        vectors[i] = bitset<MAXN>(s); // 移除reverse
    }

    VectorSet solver;
    solver.n = n;
    solver.d = d;
    solver.gaussian_elimination(vectors);

    auto ans = solver.solve();
    cout << "Selected original indices:";
    for (int x : ans) cout << " " << x;
    cout << endl;
}
