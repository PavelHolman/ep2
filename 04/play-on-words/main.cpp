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

void solve() {
    int n;
    cin >> n;

    vvi adj(26);
    vi deg_in(26), deg_out(26);

    int start = 26;

    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        int const s = str.front() - 'a', t = str.back() - 'a';
        start = min(s, start);

        adj[s].emplace_back(t);
        adj[t].emplace_back(s);
        deg_out[s]++;
        deg_in[t]++;
    }

    vb vis(26, false);
    for (int i = 0; i < 26; i++) { vis[i] = (deg_in[i] == 0 && deg_out[i] == 0); }
    function<void(int)> const dfs = [&dfs, &adj, &vis](int const u) -> void {
        if (vis[u]) return;
        vis[u] = true;
        for (int v: adj[u]) dfs(v);
    };
    dfs(start);

    if (!all_of(all(vis), [](bool const b) { return b; })) {
        cout << "The door cannot be opened." << endl;
        return;
    }

    bool fs = false, fe = false;

    for (int i = 0; i < 26; i++) {
        int d = deg_in[i] - deg_out[i];
        if (d == 0) continue;
        if (d == -1 && !fs) {
            fs = true;
            continue;
        }
        if (d == 1 && !fe) {
            fe = true;
            continue;
        }

        cout << "The door cannot be opened." << endl;
        return;
    }

    if (fs != fe) {
        cout << "The door cannot be opened." << endl;
        return;
    }

    cout << "Ordering is possible." << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (int t = 0; t < tc; t++) { solve(); }
    return 0;
}
