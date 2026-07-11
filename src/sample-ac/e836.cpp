#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<int> order;
        unordered_map<int, int> freq;

        int max_freq = 0;
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            if (freq.find(x) == freq.end()) {
                order.push_back(x);
            }
            freq[x]++;
            if (freq[x] > max_freq) {
                max_freq = freq[x];
            }
        }

        cout << order.size() << "\n";

        if (max_freq <= 1) {
            cout << "NO\n";
        } else {
            bool first = true;
            for (int x : order) {
                if (freq[x] == max_freq) {
                    if (!first) cout << " ";
                    cout << x;
                    first = false;
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
