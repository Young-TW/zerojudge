#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string special, grand;
    while (cin >> special) {
        if (!(cin >> grand)) break;
        vector<string> first(3);
        for (int i = 0; i < 3; ++i) cin >> first[i];
        string add1, add2;
        cin >> add1 >> add2;
        int N;
        cin >> N;
        long long totalBest = 0, totalWorst = 0;
        const long long INF = (1LL << 60);

        auto prize = [&](const string &num) -> int {
            if (num == special) return 10000000;
            if (num == grand)   return 2000000;
            for (const string &f : first)
                if (num == f) return 200000;
            const int val[5] = {40000, 10000, 4000, 1000, 200};
            const int len[5] = {7, 6, 5, 4, 3};
            for (int i = 0; i < 5; ++i) {
                for (const string &f : first) {
                    if (num.substr(8 - len[i]) == f.substr(8 - len[i]))
                        return val[i];
                }
            }
            string last3 = num.substr(5, 3);
            if (last3 == add1 || last3 == add2) return 200;
            return 0;
        };

        for (int i = 0; i < N; ++i) {
            string rec;
            cin >> rec;
            size_t pos = rec.find('*');
            long long best = 0, worst = INF;
            if (pos == string::npos) {
                int p = prize(rec);
                best = worst = p;
            } else {
                for (char d = '0'; d <= '9'; ++d) {
                    string cand = rec;
                    cand[pos] = d;
                    int p = prize(cand);
                    if (p > best) best = p;
                    if (p < worst) worst = p;
                }
            }
            totalBest += best;
            totalWorst += worst;
        }
        cout << totalBest << ' ' << totalWorst << "\n";
    }
    return 0;
}
