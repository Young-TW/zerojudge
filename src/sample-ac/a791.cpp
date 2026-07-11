#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long last_used[1024] = {0};
    bool in_cache[1024] = {false};
    vector<int> cache;
    cache.reserve(16);

    long long timer = 0;
    int hit_count = 0;
    int total_count = 0;

    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int p;
        bool has_num = false;
        while (ss >> p) {
            has_num = true;
            total_count++;
            if (in_cache[p]) {
                hit_count++;
                last_used[p] = ++timer;
            } else {
                if (cache.size() == 16) {
                    long long min_time = LLONG_MAX;
                    int lru_idx = 0;
                    for (int i = 0; i < 16; ++i) {
                        if (last_used[cache[i]] < min_time) {
                            min_time = last_used[cache[i]];
                            lru_idx = i;
                        }
                    }
                    in_cache[cache[lru_idx]] = false;
                    cache[lru_idx] = p;
                    in_cache[p] = true;
                } else {
                    cache.push_back(p);
                    in_cache[p] = true;
                }
                last_used[p] = ++timer;
            }
        }
        if (has_num) {
            double rate = (double)hit_count / total_count * 100.0;
            cout << "cache hit rate: " << fixed << setprecision(2) << rate << "%\n";
        }
    }

    return 0;
}
