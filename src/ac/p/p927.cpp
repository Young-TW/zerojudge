#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<string> family_names(N);
        vector<long long> sums(N, 0);
        map<string, vector<int>> spice_to_families;
        
        for (int i = 0; i < N; ++i) {
            cin >> family_names[i];
            int K;
            cin >> K;
            set<string> seen;
            for (int j = 0; j < K; ++j) {
                string spice;
                cin >> spice;
                if (seen.find(spice) == seen.end()) {
                    seen.insert(spice);
                    spice_to_families[spice].push_back(i);
                }
            }
        }
        
        int M;
        cin >> M;
        for (int i = 0; i < M; ++i) {
            string spice;
            long long amount;
            cin >> spice >> amount;
            if (spice_to_families.count(spice)) {
                for (int fam_idx : spice_to_families[spice]) {
                    sums[fam_idx] += amount;
                }
            }
        }
        
        long long max_sum = -1;
        int best_idx = 0;
        for (int i = 0; i < N; ++i) {
            if (sums[i] > max_sum) {
                max_sum = sums[i];
                best_idx = i;
            }
        }
        cout << family_names[best_idx] << "\n";
    }
    
    return 0;
}
