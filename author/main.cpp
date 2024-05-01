//region Template
#include <bits/stdc++.h>

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

using namespace std;

#define int long long

using ll = intmax_t;
using ull = uintmax_t;
using ld = long double;
using fast = int_fast32_t;
using ufast = uint_fast32_t;
template<typename T> using uset = unordered_set<T>;
template<typename K, typename V> using umap = unordered_map<K, V>;


template<typename T, typename K>
ostream &operator<<(ostream &os, const pair<T, K> &p) {
    return os << p.first << " " << p.second;
}

template<typename T, typename K>
istream &operator>>(istream &is, pair<T, K> &p) { return is >> p.first >> p.second; }

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const auto &item: v) os << item << " ";
    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &v) {
    for (auto &item: v) is >> item;
    return is;
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
#define usz(x) (ull)(x).size()
#define MAX(TYPE) numeric_limits<TYPE>::max()
#define MIN(TYPE) numeric_limits<TYPE>::min()

using pii = pair<int, int>;
using vb = vector<bool>;
using vp = vector<pii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvp = vector<vp>;

//endregion

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vvp adj(n);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    pii max = {0, -1};

    vi d(n);
    function<bool(int, int, int)> dfs = [&dfs, &adj, &d, &max](int const u, int const c, int const p) {
        if (d[u] != -1) return true;
        max = ::max(max, {d[u] = d[p] + c, u});
        return any_of(all(adj[u]), [&dfs, u, p](pii const &v) {
            if (v.first == p) return false;
            return dfs(v.first, v.second, u);
        });
    };

    d.assign(n, -1);
    if (dfs(0, 1, 0)) {
        cout << "YES" << endl;
        return;
    }

    auto const s = max.second;
    max = {0, -1};

    d.assign(n, -1);
    dfs(s, 1, s);

    if (max.first >= k)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (int t = 0; t < tc; t++) { solve(); }
    return 0;
}
