#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    while (cin >> M >> N) {
        vector<int> cache;          // FIFO queue
        int miss = 0;
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            bool found = false;
            for (int v : cache) {
                if (v == x) { found = true; break; }
            }
            if (found) continue;    // already in memory
            ++miss;                 // dictionary lookup
            if ((int)cache.size() == M) {
                cache.erase(cache.begin()); // evict oldest
            }
            cache.push_back(x);     // store new word
        }
        cout << miss << '\n';
    }
    return 0;
}
