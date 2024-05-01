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

using TestCase = tuple<int, int, int, map<pii, int>>;

vector<TestCase> generate_test_cases() {
    vector<TestCase> test_cases;
    srand(time(nullptr));

    int const T = rand() % 1000 + 1;

    for (int t = 0; t < T; ++t) {
        int const n = rand() % 999 + 2;
        int const m = min(n * (n - 1) / 2, rand() % 1000 + 1ll);
        int const k = rand() % 100'000 + 1;

        map<pii, int> streets;
        while (sz(streets) != m) {
            int u = rand() % n + 1;
            int v = rand() % n + 1;
            while (u == v) v = rand() % n + 1;
            int l = rand() % 1000 + 1;
            streets.emplace(pii{min(u, v), max(u, v)}, l);
        }

        test_cases.emplace_back(n, m, k, streets);
    }

    return test_cases;
}

void print_test_cases(vector<TestCase> const &test_cases) {
    cout << sz(test_cases) << endl;
    for (const auto &test_case: test_cases) {
        auto const &[n, m, k, streets] = test_case;

        cout << n << " " << m << " " << k << "\n";
        for (const auto &street: streets) {
            cout << street << '\n';
        }
    }

    cout << flush;
}

signed main() {
    vector<TestCase> test_cases = generate_test_cases();
    print_test_cases(test_cases);

    return 0;
}
