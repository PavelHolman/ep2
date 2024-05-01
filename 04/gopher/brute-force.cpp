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

int T;

void solve() {
    int m, n, k;
    cin >> m >> n >> k;

    auto A = vp(m), B = vp(n);
    cin >> A >> B;

    auto const d = [&A, &B](int const u, int const v) -> double {
        if (u >= sz(A) || v >= sz(B)) return MAX(double);
        auto const [ax, ay] = A[u];
        auto const [bx, by] = B[v];
        return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
    };

    auto D = vector(m, vector(n, double()));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            D[i][j] = d(i, j);
        }
    }

    // Choose all combinations of m - k non-adjacent edges, take max weight, compare all max weights
    auto mn = MAX(double);
    auto P = vi(n);
    iota(all(P), 0);

    do {
        auto mx = 0.;
        for (int i = 0; i < m - k; i++) { mx = max(mx, D[i][P[i]]); }
        mn = min(mx, mn);
    } while (next_permutation(all(P)));

    if (mn == MAX(double)) {
        cout << "Case #" << T << ":\nToo bad.\n" << endl;
        return;
    }

    cout << "Case #" << T << ":\n" << fixed << setprecision(3) << ceil(mn * 1000) / 1000 << '\n' << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;
    for (T = 1; T <= tc; T++) { solve(); }
    return 0;
}
