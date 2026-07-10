#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long k, m;
    while (cin >> k >> m) {
        vector<set<long long>> table(m);
        for (long long i = 0; i < k; i++) {
            int op;
            cin >> op;
            if (op == 1) {
                long long N;
                cin >> N;
                table[N % m].insert(N);
            } else if (op == 2) {
                long long N;
                cin >> N;
                table[N % m].erase(N);
            } else {
                cout << "===== s =====\n";
                for (long long j = 0; j < m; j++) {
                    cout << '[' << setw(3) << setfill('0') << j << "]:";
                    if (table[j].empty()) {
                        cout << "NULL";
                    } else {
                        bool first = true;
                        for (long long v : table[j]) {
                            if (!first) cout << " -> ";
                            cout << v;
                            first = false;
                        }
                        cout << " -> NULL";
                    }
                    cout << '\n';
                }
                cout << "===== e =====\n";
            }
        }
    }
    return 0;
}
