#include <algorithm>
#include <iostream>
#include <vector>

const int N = 200005;
const int INF = 1e9;

int n;
int a[N];
std::vector<int> pos[N];
int global_ans;

namespace MinTree {
int tree[4 * N];
void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = std::min(tree[2 * node], tree[2 * node + 1]);
}
int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l || l > r) return INF;
    if (l <= start && end <= r) return tree[node];
    int mid = start + (end - start) / 2;
    return std::min(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}
} // namespace MinTree

namespace SumTree {
struct Node {
    int min_v, max_v;
    long long lazy;
};
Node tree[4 * (N + 1)];
int initial_S[N + 1];

void pull(int node) {
    tree[node].min_v = std::min(tree[2 * node].min_v, tree[2 * node + 1].min_v);
    tree[node].max_v = std::max(tree[2 * node].max_v, tree[2 * node + 1].max_v);
}
void push(int node, int start, int end) {
    if (tree[node].lazy == 0) return;
    tree[node].min_v += tree[node].lazy;
    tree[node].max_v += tree[node].lazy;
    if (start != end) {
        tree[2 * node].lazy += tree[node].lazy;
        tree[2 * node + 1].lazy += tree[node].lazy;
    }
    tree[node].lazy = 0;
}
void build(int node, int start, int end) {
    tree[node].lazy = 0;
    if (start == end) {
        tree[node].min_v = tree[node].max_v = initial_S[start];
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    pull(node);
}
void update(int node, int start, int end, int l, int r, int val) {
    push(node, start, end);
    if (r < start || end < l || l > r) return;
    if (l <= start && end <= r) {
        tree[node].lazy += val;
        push(node, start, end);
        return;
    }
    int mid = start + (end - start) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    pull(node);
}
std::pair<int, int> query(int node, int start, int end, int l, int r) {
    if (r < start || end < l || l > r) return {INF, -INF};
    push(node, start, end);
    if (l <= start && end <= r) return {tree[node].min_v, tree[node].max_v};
    int mid = start + (end - start) / 2;
    auto p1 = query(2 * node, start, mid, l, r);
    auto p2 = query(2 * node + 1, mid + 1, end, l, r);
    return {std::min(p1.first, p2.first), std::max(p1.second, p2.second)};
}
} // namespace SumTree

void solve() {
    std::cin >> n;
    for (int i = 0; i <= n + 1; ++i) {
        pos[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        pos[a[i]].push_back(i);
    }

    MinTree::build(1, 1, n);

    SumTree::initial_S[0] = 0;
    for (int i = 1; i <= n; ++i) {
        SumTree::initial_S[i] = i;
    }
    SumTree::build(1, 0, n);

    global_ans = 0;

    for (int x = 1; x <= n; ++x) {
        auto overall_range = SumTree::query(1, 0, n, 0, n);
        if (overall_range.second >= overall_range.first) {
            int L = n + 1, R = 0;

            // Find smallest L = k+1 s.t. exists r > k with S[r] >= S[k].
            // This is true if S[k] <= max(S[k+1...n]).
            // Smallest L s.t. exists l<=L and r>=l with S[r]>=S[l-1].
            // A sufficient condition for this is max(S[1...n]) >= min(S[0...L-1]).
            int max_S_after_0 = (n > 0) ? SumTree::query(1, 0, n, 1, n).second : -INF;
            int l_bound = n + 1;
            int low = 1, high = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (max_S_after_0 >= SumTree::query(1, 0, n, 0, mid - 1).first) {
                    l_bound = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            L = l_bound;

            // Find largest R s.t. exists l<=R with S[R] >= S[l-1].
            // This is true if S[R] >= min(S[0...R-1]).
            // A sufficient condition is max(S[R...n]) >= min(S[0...n-1]).
            int min_S_before_n = (n > 0) ? SumTree::query(1, 0, n, 0, n - 1).first : 0;
            int r_bound = 0;
            low = 1, high = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (SumTree::query(1, 0, n, mid, n).second >= min_S_before_n) {
                    r_bound = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            R = r_bound;

            if (L <= R) {
                int min_a = MinTree::query(1, 1, n, L, R);
                global_ans = std::max(global_ans, x - min_a);
            }
        }

        if (x <= n) {
            for (int j : pos[x]) {
                SumTree::update(1, 0, n, j, n, -2);
            }
        }
    }

    std::cout << global_ans << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
