#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        int num_ulls = (M + 63) / 64;
        vector<unsigned long long> masks(N * num_ulls, 0);
        vector<int> counts(N, 0);
        
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < M; ++j) {
                if (s[j] == '1') {
                    masks[i * num_ulls + j / 64] |= (1ULL << (j % 64));
                    counts[i]++;
                }
            }
        }

        long long S = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                int intersection = 0;
                for (int k = 0; k < num_ulls; ++k) {
                    intersection += __builtin_popcountll(masks[i * num_ulls + k] & masks[j * num_ulls + k]);
                }
                int union_size = counts[i] + counts[j] - intersection;
                if (intersection * 5 >= union_size * 4) {
                    S++;
                }
            }
        }

        double total_pairs = static_cast<double>(N) * (N - 1) / 2.0;
        double percentage = (S / total_pairs) * 100.0;
        cout << fixed << setprecision(2) << percentage << "\n";
    }

    return 0;
}
