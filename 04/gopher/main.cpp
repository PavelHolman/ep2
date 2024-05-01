//region Template
#include <bits/stdc++.h>

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

using namespace std;

#include <bits/extc++.h>

using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define int long long
#define double long double

using ll = intmax_t;
using ull = uintmax_t;
using ld = double;
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
using vd = vector<double>;
using vvi = vector<vi>;
using vvd = vector<vd>;

//endregion

tuple<int, int, vvi, vvi, vvd> read_input(int const m, int const n) {
    int const N = m + n + 2;
    vvi adj(N);
    vvi capacity(N, vi(N));
    vvd cost(N, vd(N));

    int const s = 0, t = N - 1;

    vp A(m), B(n);
    cin >> A >> B;

    auto const d = [&A, &B](int const u, int const v) -> double {
        auto const [ax, ay] = A[u];
        auto const [bx, by] = B[v];
        return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
    };

    for (int u = 0; u < m; u++) {
        int const a = u + 1;
        adj[s].emplace_back(a);
        capacity[s][a] = 1;
    }

    for (int u = 0; u < n; u++) {
        int const b = u + 1 + m;
        adj[b].emplace_back(t);
        capacity[b][t] = 1;
    }

    for (int u = 0; u < m; u++) {
        for (int v = 0; v < n; v++) {
            double const c = d(u, v);

            int const a = u + 1;
            int const b = v + 1 + m;
            adj[a].emplace_back(b);
            adj[b].emplace_back(a);
            capacity[a][b] = 1;
            cost[a][b] = c;
            cost[b][a] = c;
        }
    }

    return {s, t, adj, capacity, cost};
}

optional<pair<int, vector<optional<int>>>>
find_aug_path(vvi const &adj, vvi const &capacity, vvd const &cost, double const max_cost, int const s, int const t) {
    vector<optional<int>> prev(sz(adj));
    prev[s] = s;
    queue<pii> q{{{s, MAX(int)}}};

    while (!q.empty()) {
        auto const [u, fl] = q.front();
        q.pop();

        if (u == t) return pair{fl, prev};

        for (int const v: adj[u]) {
            if (prev[v].has_value()) continue;
            if (capacity[u][v] == 0) continue;
            if (cost[u][v] > max_cost) continue;
            q.emplace(v, min(fl, capacity[*(prev[v] = u)][v]));
        }
    }

    return {};
}

int ford_fulkerson(vvi const &adj, vvi capacity, vvd const &cost, double const max_cost, int const s, int const t) {
    int flow = 0;

    while (auto const aug = find_aug_path(adj, capacity, cost, max_cost, s, t)) {
        auto const &[aug_flow, prev] = *aug;
        
        flow += aug_flow;
        for (int v = t; v != s; v = *prev[v]) {
            int const u = *prev[v];
            capacity[u][v] -= aug_flow;
            capacity[v][u] += aug_flow;
        }
    }

    return flow;
}

void solve(int const T) {
    int m, n, k;
    cin >> m >> n >> k;

    auto const [s, t, adj, capacity, cost] = read_input(m, n);

    if (m - k > n) {
        cout << "Case #" << T << ":\nToo bad.\n" << endl;
        return;
    }

    if (m - k == 0) {
        cout << "Case #" << T << ":\n0.000\n" << endl;
        return;
    }

    optional<double> min_cost;

    Tree<double> costs;
    for (int u = 0; u < m; u++) {
        for (int v = 0; v < n; v++) {
            int const a = u + 1;
            int const b = v + 1 + m;
            costs.insert(cost[a][b]);
        }
    }

    int l = 0, r = sz(costs);
    while (l < r) {
        int const mid = (l + r) / 2;
        double const max_cost = *costs.find_by_order(mid);
        auto const flow = ford_fulkerson(adj, capacity, cost, max_cost, s, t);

        if (flow >= m - k) {
            r = mid;
            min_cost = min(min_cost.value_or(MAX(double)), max_cost);
        } else {
            l = mid + 1;
        }
    }

    if (!min_cost.has_value()) {
        cout << "Case #" << T << ":\nToo bad." << endl;
        return;
    }

    cout << "Case #" << T << ":\n" << fixed << setprecision(3) << ceil(*min_cost * 1000) / 1000 << '\n' << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (int T = 1; T <= tc; T++) { solve(T); }
    return 0;
}
