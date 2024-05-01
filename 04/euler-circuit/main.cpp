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

//endregion

using Adj = vvi;
using Vertices = vi;
using Edges = vp;

optional<pair<int, vector<optional<int>>>>
find_aug_path(Adj const &adj, int const s, int const t, vvi const &c) {
    vector<optional<int>> prev(sz(adj));
    prev[s] = s;
    queue<pii> q{{{s, MAX(int)}}};

    while (!q.empty()) {
        auto const [u, fl] = q.front();
        q.pop();

        if (u == t) return pair{fl, prev};

        for (int const v: adj[u]) {
            if (prev[v].has_value()) continue;
            if (c[u][v] == 0) continue;
            q.emplace(v, min(fl, c[*(prev[v] = u)][v]));
        }
    }

    return {};
}

vvi ford_fulkerson(Adj const &adj, int const s, int const t, vvi const &c) {
    auto r = c;
    while (auto const aug = find_aug_path(adj, s, t, r)) {
        auto const &[aug_flow, prev] = *aug;

        for (int v = t; v != s; v = *prev[v]) {
            int const u = *prev[v];
            r[u][v] -= aug_flow;
            r[v][u] += aug_flow;
        }
    }

    auto const N = sz(adj);
    auto f = vector(N, vector(N, 0ll));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            f[i][j] = c[i][j] - r[i][j];
        }
    }

    return f;
}

void solve() {
    int n, m;
    cin >> n >> m;

    Vertices V(n);
    Edges D, U;

    iota(all(V), 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        char ch;
        cin >> u >> v >> ch;

        switch (ch) {
            case 'U':
                U.emplace_back(u, v);
                break;
            case 'D':
                D.emplace_back(u, v);
                break;
            default:
                throw;
        }
    }

    auto const N = (sz(V) + sz(U) + 2ll);
    auto const s = 0ll, t = N - 1;
    vvi g(N);
    auto capacity = vector(N, vector(N, 0ll));

    auto const d = [&U, &D](int const x) {
        int deg = 0;
        for (auto const &[u, v]: U) {
            deg += u == x;
            deg += v == x;
        }
        for (auto const &[u, v]: D) {
            deg += v == x;
            deg -= u == x;
        }

        return deg / 2;
    };

    for (int i = 0; i < sz(U); i++) {
        int const e = i + sz(V) + 1;
        auto const [u, v] = U[i];
        capacity[s][e] = 1;
        g[s].emplace_back(e);

        capacity[e][u] = 1;
        capacity[e][v] = 1;
        g[e].emplace_back(u);
        g[e].emplace_back(v);

        g[u].emplace_back(e);
        g[v].emplace_back(e);
    }

    for (int i = 0; i < sz(V); i++) {
        int const u = i + 1;
        capacity[u][t] = d(u);
        g[u].emplace_back(t);
    }

    auto const f = ford_fulkerson(g, s, t, capacity);

    for (int i = 0; i < sz(g); i++) {
        if (f[0][i] == capacity[0][i]) continue;
        cout << "No euler circuit exist" << endl;
        return;
    }

    Adj adj(n);
    for (int i = 0; i < sz(D); i++) {
        auto [u, v] = D[i];
        u--, v--;
        adj[u].emplace_back(v);
    }
    for (int i = 0; i < sz(U); i++) {
        auto const e = i + sz(V) + 1;
        auto [u, v] = U[i];
        u--, v--;
        if (f[e][u + 1]) adj[u].emplace_back(v);
        else if (f[e][v + 1]) adj[v].emplace_back(u);
        else throw;
    }


    vi deg_in(sz(adj)), deg_out(sz(adj));

    for (int u = 0; u < sz(adj); u++) {
        for (int v: adj[u]) {
            deg_out[u]++;
            deg_in[v]++;
        }
    }

    vi ans;

    stack<int> st;
    st.emplace(0);

    while (!st.empty()) {
        auto const v = st.top();
        if (!sz(adj[v])) {
            ans.emplace_back(v);
            st.pop();
            continue;
        }

        st.emplace(adj[v].back());
        adj[v].pop_back();
    }
    for (int &x: ans) x++;
    reverse(all(ans));
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (int t = 0; t < tc; t++) { solve(); }
    return 0;
}
