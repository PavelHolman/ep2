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

void solve() {
    int n, m;
    cin >> n >> m;

    vector d(n, vector(n, optional<int>()));
    for (int i = 0; i < n; i++) d[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;

        d[v][u] = d[u][v] = w;
    }


    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (!d[i][k].has_value() || !d[k][j].has_value()) continue;

                if (!d[i][j].has_value() || d[i][j] > *d[i][k] + *d[k][j])
                    d[i][j] = *d[i][k] + *d[k][j];
            }

    int mx = MIN(int);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            auto x = d[i][j];
            if (x.has_value()) {
                mx = max(mx, *x);
            } else {
                cout << "Bez spojeni neni veleni!" << endl;
                return;
            }
        }

    cout << "Nejvetsi vzdalenost je " << mx << "." << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (int t = 0; t < tc; t++) { solve(); }
    return 0;
}
