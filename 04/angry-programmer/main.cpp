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

template<typename T, typename K>
ostream &operator<<(ostream &os, const pair<T, K> &p) {
    return os << p.first << " " << p.second;
}

template<typename T, typename K>
istream &operator>>(istream &is, pair<T, K> &p) { return is >> p.first >> p.second; }

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

//endregion

class M {
    vvi _f;
public:
    explicit M(int const n)
            : _f(n, vi(n, 0)) {
    }

    int &operator()(int const u) { return _f[u][u]; }

    int operator()(int const u) const { return _f[u][u]; }

    int &operator()(int const u, int const v) { return _f[u][v]; }

    int operator()(int const u, int const v) const { return _f[u][v]; }
};

class C : public M {
    using M::M;
};

class F : public M {
    using M::M;
};

class R {
    M const &_f;
    C const &_c;
public:
    explicit R(C const &c, M const &f)
            : _f(f), _c(c) {
    }

    int operator()(int const u, int const v) const { return _c(u, v) - _f(u, v) + (u == v ? 0 : _f(v, u)); }
};

using Adj = vvi;
using Path = vp;

pair<Adj, C> read_input(int const n, int const m, int const s, int const t) {
    auto adj = Adj(n);
    auto c = C(n);
    c(s) = c(t) = MAX(int);

    for (int i = 1; i < n - 1; i++) {
        int u, cap;
        cin >> u >> cap;
        u--;
        c(u) = cap;
    }

    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        u--, v--;
        c(u, v) = c(v, u) = cap;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    return {adj, c};
}

optional<Path> find_aug_path(vvi const &adj, int const s, int const t, C const &c, M const &f) {
    auto q = queue<int>{{s}};
    auto prev = vector<optional<int>>(sz(adj));
    prev[s] = s;

    while (!q.empty()) {
        auto const u = q.front();
        q.pop();

        if (u == t) {
            Path path{{t, t}};
            for (int p = u; p != s; p = *prev[p]) {
                path.emplace_back(*prev[p], p);
                path.emplace_back(*prev[p], *prev[p]);
            }
            reverse(all(path));
            return path;
        }

        for (auto const v: adj[u]) {
            if (prev[v].has_value()) continue;
            if (c(u, v) == f(u, v) || c(v) == f(v)) continue;
            prev[v] = u;
            q.emplace(v);
        }
    }

    return {};
}

M ford_fulkerson(Adj const &adj, int const s, int const t, C const &c) {
    auto const n = sz(adj);
    auto f = F(n);
    auto const r = R(c, f);

    while (true) {
        auto const path = find_aug_path(adj, s, t, c, f);

        if (!path.has_value()) return f;

        vi rs(sz(*path));
        transform(all(*path), begin(rs), [&r](pii const &e) -> int { return r(e.first, e.second); });
        auto const eps = *min_element(all(rs));

        for (auto const &[u, v]: *path) {
            auto const delta = u == v ? 0 : min(f(v, u), eps);
            f(v, u) -= delta;
            f(u, v) += eps - delta;
        }
    }
}

void solve(int const n, int const m, int const s, int const t) {
    auto const [adj, c] = read_input(n, m, s, t);
    auto const f = ford_fulkerson(adj, s, t, c);

    cout << f(s) << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int m, n;
        cin >> n >> m;
        if (!n && !m) break;
        solve(n, m, 0, n - 1);
    }
    return 0;
}
