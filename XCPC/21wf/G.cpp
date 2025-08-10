#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353, R = 3;
using ll = long long;
int qpow(int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1) ans = ans * 1ll * x % mod;
        x = x * 1ll * x % mod;
        y >>= 1;
    }
    return ans;
}
int _(int x) { return x >= mod ? x - mod : x; }
const int L2 = 20;
struct NTT {
    int L = -1;
    vector<int> rev, rt;
    void init(int l) {
        int t = L;
        L = l;
        rev.resize(2 << L);
        rt.resize(2 << L);
        for (int i = t + 1; i <= L; i++) {
            int *w = rt.data() + (1 << i);
            w[0] = 1;
            int w1 = qpow(R, (mod - 1) >> i);
            for (int j = 1; j < 1 << i; j++) w[j] = w[j - 1] * 1ll * w1 % mod;
            int *r = rev.data() + (1 << i);
            for (int j = 1; j < 1 << i; j++) r[j] = (r[j >> 1] >> 1) | ((j & 1) << (i - 1));
        }
    }
    void operator()(int *a, int lgn, int d = 1) {
        if (L < lgn) init(lgn);
        int n = 1 << lgn;
        int *r = rev.data() + (1 << lgn);
        for (int i = 0; i < n; i++)
            if (r[i] < i) swap(a[i], a[r[i]]);
        for (int i = 1; i < n; i <<= 1) {
            int *w = rt.data() + (i << 1);
            for (int j = 0; j < n; j += i << 1) {
                for (int k = 0; k < i; k++) {
                    int y = w[k] * 1ll * a[i + j + k] % mod;
                    a[i + j + k] = _(a[j + k] + mod - y);
                    a[j + k] = _(a[j + k] + y);
                }
            }
        }
        if (d == -1) {
            reverse(a + 1, a + n);
            int inv = qpow(n, mod - 2);
            for (int i = 0; i < n; i++) a[i] = a[i] * 1ll * inv % mod;
        }
    }
} ntt;

const int N = 2048;
const int LGN = 11;
const int B = 101;
const int BI = qpow(B, mod - 2);
int n;
int pat[N][N];
int mat[N][N];
int x[N];
int mult[N][N];
int n1, m1;
int n2, m2;

void ntt_col(int arr[N][N], ll i, ll lgn, ll d = 1) {
    static int tmp[N];
    for (int j = 0; j < N; j++) tmp[j] = arr[j][i];
    ntt(tmp, lgn, d);
    for (int j = 0; j < N; j++) arr[j][i] = tmp[j];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n1 >> m1;

    ll v = 1, targ = 0;
    for (int i = 1; i <= n1; i++)
        for (int j = 1; j <= m1; j++) {
            cin >> pat[i][j];
            v = v * B % mod;
            targ = (targ + v * pat[i][j]) % mod;
            mult[n1 - i][m1 - j] = pat[i][j] ? v : 0;
        }
    cin >> n2 >> m2;
    for (int i = 1; i <= n2; i++)
        for (int j = 1; j <= m2; j++) {
            cin >> mat[i][j];
        }

    for (int i = 0; i < N; i++) {
        ntt(mat[i], LGN);
        ntt(mult[i], LGN);
    }
    for (int i = 0; i < N; i++) {
        ntt_col(mat, i, LGN);
        ntt_col(mult, i, LGN);
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            mat[i][j] = mat[i][j] * 1ll * mult[i][j] % mod;
        }
    for (int i = 0; i < N; i++) {
        ntt_col(mat, i, LGN, -1);
    }
    for (int i = 0; i < N; i++) {
        ntt(mat[i], LGN, -1);
    }
    int cnt = 0;
    for (int i = 1 + n1 - 1; i <= n2; i++)
        for (int j = 1 + m1 - 1; j <= m2; j++) {
            if (mat[i][j] == targ) {
                ++cnt;
            }
        }
    cout << cnt << '\n';
    for (int i = 1 + n1 - 1; i <= n2; i++)
        for (int j = 1 + m1 - 1; j <= m2; j++) {
            if (mat[i][j] == targ) {
                cout << i - n1 + 1 << " " << j - m1 + 1 << '\n';
            }
        }

    return 0;
}
