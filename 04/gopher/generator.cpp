#include <bits/stdc++.h>

int main() {
    auto ofs = std::ofstream("input2.txt");
    int const t = 1000;
    ofs << t << "\n";
    for (int tc = 0; tc < t; tc++) {
        int const M = 8;//, N = rand() % 10, k = rand() % 10;
        int const N = M, k = 0;
        ofs << M << " " << N << " " << k << '\n';

        for (int i = 0; i < M; i++) {
            int const x = rand() % 10, y = rand() % 10;
            ofs << x << " " << y << '\n';
        }

        for (int j = 0; j < N; j++) {
            int const x = rand() % 10, y = rand() % 10;
            ofs << x << " " << y << '\n';
        }
    }
    
    ofs << std::flush;
}
