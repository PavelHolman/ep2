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

using pdd = pair<double, double>;

pdd operator+(pdd const &a, pdd const &b) {
    return {a.first + b.first, a.second + b.second};
}

pdd operator-(pdd const &a, pdd const &b) {
    return {a.first - b.first, a.second - b.second};
}

double cross(pdd const &a, pdd const &b) {
    return a.first * b.second - b.first * a.second;
}

double dot(pdd const &a, pdd const &b) {
    return a.first * b.first + a.second * b.second;
}

double mag(pdd const &a) {
    return sqrt(pow(a.first, 2) + pow(a.second, 2));
}

void solve(int n) {
    vector<pair<pdd, double>> a(n);
    pdd s, t;
    cin >> a >> s >> t;

    double see = 0, fly = mag(s - t);

    for (auto const &[p, r]: a) {
        double const d = cross(p - s, p - t) / mag(t - s);

        if (d >= r) continue;

        double const chord = 2 * sqrt(r * r - d * d);
        double const sector = 2 * r * acos(d / r);
        
        see += chord;
        fly += sector - chord;
    }

    cout << fixed << setprecision(2) << "Superman sees thru " << see << " units, and flies " << fly << " units."
         << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int t;
        cin >> t;
        if (t == -1) break;
        solve(t);
    }
    return 0;
}
