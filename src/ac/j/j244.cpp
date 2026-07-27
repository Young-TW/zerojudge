#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K, N;
    if (!(cin >> K >> N)) return 0;

    unordered_set<string> lucky_K, lucky_K2, lucky_K4, lucky_3;
    lucky_K.reserve(3);
    lucky_K2.reserve(3);
    lucky_K4.reserve(3);
    lucky_3.reserve(3);

    for (int i = 0; i < 3; ++i) {
        string s;
        cin >> s;
        lucky_K.insert(s);
        if (K >= 3) {
            lucky_K2.insert(s.substr(K - (K - 2)));
            lucky_K4.insert(s.substr(K - (K - 4)));
            lucky_3.insert(s.substr(K - 3));
        }
    }

    long long total_prize = 0;

    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        
        if (lucky_K.count(s)) {
            total_prize += 500000;
        } else if (K >= 3 && lucky_K2.count(s.substr(2))) {
            total_prize += 10000;
        } else if (K >= 3 && lucky_K4.count(s.substr(4))) {
            total_prize += 1000;
        } else if (K >= 3 && lucky_3.count(s.substr(K - 3))) {
            total_prize += 300;
        }
    }

    cout << total_prize << "\n";

    return 0;
}
