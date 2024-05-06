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

double convex_hull(vp &P) {
    if (sz(P) <= 1) return 0;

    auto const it = min_element(all(P));
    auto const p0 = *it;
    P.erase(it);

    auto const angle = [](pii const &a, pii const &b) {
        auto const dx = b.first - a.first;
        auto const dy = b.second - a.second;
        return atan2((double) dy, (double) dx);
    };

    sort(all(P), [&angle, p0](pii const &a, pii const &b) { return angle(p0, a) < angle(p0, b); });

    auto const dir = [](pii const &a, pii const &b, pii const &c) {
        auto const [x1, y1] = a;
        auto const [x2, y2] = b;
        auto const [x3, y3] = c;
        return (x3 - x2) * (y2 - y1) - (y3 - y2) * (x2 - x1);
    };

    vp st{{p0}};

    for (auto const &p: P) {
        while (sz(st) > 1 && dir(st[sz(st) - 2], st.back(), p) >= 0) { st.pop_back(); }
        st.emplace_back(p);
    }

    auto const d = [](pii const &a, pii const &b) {
        auto const [x1, y1] = a;
        auto const [x2, y2] = b;
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    };

    double sum = d(p0, st.back());

    for (int i = 1; i < sz(st); i++) {
        sum += d(st[i], st[i - 1]);
    }

    return sum;
}

void solve(int const n) {
    vector<pair<pii, pii>> a(n);
    cin >> a;

    vector<pair<int, pair<int, bitset<24>>>> map;

    for (bitset<24> b = 0; b.to_ulong() < (1ull << n); b = b.to_ulong() + 1) {
        int V = 0;
        int L = 0;

        for (int i = 0; i < n; i++) {
            auto const [v, l] = a[i].second;

            if (!b[i]) {
                V += v;
                L += l;
            }
        }

        map.emplace_back(V, pair{L, b});
    }

    sort(all(map), [](auto const &a, auto const &b) { return a.first < b.first; });

    for (auto &[V, pp]: map) {
        auto &[L, b] = pp;
        vp P;

        for (int i = 0; i < n; i++) { if (b[i]) P.emplace_back(a[i].first); }

        if (convex_hull(P) <= (double) L) {
            cout << "The lost value is " << V << "." << endl;
            return;
        }
    }

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        solve(n);
    }

    return 0;
}
