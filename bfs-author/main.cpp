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
    int n, m, s, t, k;
    cin >> n >> m >> s >> t >> k;

    vvp adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
    }

    vvp prev_cost(n + 1);
    vector<optional<int>> depth(n + 1);
    depth[s] = 0;
    queue<int> q{{s}};

    while (!q.empty()) {
        auto const u = q.front();
        q.pop();

        if (u == t) goto End;

        for (auto const &[v, c]: adj[u]) {
            if (prev_cost[v].empty()) {
                prev_cost[v].emplace_back(u, c);
                depth[v] = *depth[u] + 1;
                q.emplace(v);
            } else if (depth[v] == *depth[u] + 1) {
                prev_cost[v].emplace_back(u, c);
            }
        }
    }

    cout << "Fail" << endl;
    return;

    End:

    vi costs;
    queue<int> tr{{t}};
    while (!tr.empty()) {
        auto const v = tr.front();
        tr.pop();

        for (auto const &[p, c]: prev_cost[v]) {
            tr.emplace(p);
            costs.emplace_back(c);
        }
    }

    if (k > sz(costs)) {
        cout << "Fail" << endl;
        return;
    }

    auto const nth = begin(costs) + k - 1;
    nth_element(begin(costs), nth, end(costs), greater<>{});
    cout << "The " << k << " is " << *nth << "." << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (int t = 0; t < tc; t++) { solve(); }
    return 0;
}
